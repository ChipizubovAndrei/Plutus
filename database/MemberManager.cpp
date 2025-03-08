#include "MemberManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseManager.h"

static QSharedPointer<MemberManager> memberManager;

QSharedPointer<MemberManager> MemberManager::instance()
{
    try
    {
        if (!memberManager)
        {
            memberManager = QSharedPointer<MemberManager>(
                new MemberManager()
            );
        }
        return memberManager;
    }
    catch (const QString& ex)
    {
        throw ex;
    }
}

MemberManager::MemberManager(QObject *parent)
	: QObject(parent),
	mMemberTableName(DatabaseManager::getMemberTableName())
{
    try
    {
        auto databaseManager = DatabaseManager::instance();
        if (!databaseManager->isConnected())
        {
            databaseManager->connectToDatabase();
        }
    }
    catch (const QString& ex)
    {
        throw ex;
    }

	QSqlQuery query(QString("SELECT * FROM %1 ORDER BY id ASC")
		.arg(mMemberTableName)
	);
	if (query.lastError().type() == QSqlError::NoError)
	{
		while (query.next())
		{
            Member member;
            member.id = query.value("id").toInt();
            member.firstName = query.value("first_name").toString();
            member.secondName = query.value("second_name").toString();
			mMembers.append(member);
		}
	}
	else
	{
		throw query.lastError().text();
	}
}

QList<Member> MemberManager::getMembers() const
{
	return mMembers;
}

void MemberManager::addMember(Member member)
{
    if (!member.isValid()) return;
    QSqlQuery query;
    query.prepare(QString("INSERT INTO ? (id, firstName, secondName) VALUES (?, ?, ?)"));
    query.bindValue(0, member.id);
    query.bindValue(1, member.firstName);
    query.bindValue(2, member.secondName);
    
    if (!query.exec())
	{
		throw query.lastError().text();
	}
    mMembers.append(member);
    emit memberAdded(member);
}

void MemberManager::removeMember(Member member)
{
    if (!member.isValid()) return;
    QSqlQuery query;
    query.prepare(QString("DELETE FROM ? WHERE id = ?"));
    query.bindValue(0, mMemberTableName);
    query.bindValue(1, member.id);
	if (!query.exec())
	{
		throw query.lastError().text(); // remove error
	}
    for (int i = 0; i < mMembers.size(); ++i)
    {
        if (mMembers[i].id = member.id) mMembers.removeAt(i);
    }
    emit memberRemoved(member);
}

void MemberManager::updateMember(Member member)
{
    if (!member.isValid()) return;
    QSqlQuery query;
    query.prepare(QString(
        "UPDATE ? SET firstName = ?, secondName = ? WHERE id = ?"));
    query.bindValue(0, mMemberTableName);
    query.bindValue(1, member.firstName);
    query.bindValue(2, member.secondName);
    query.bindValue(3, member.id);
    
	if (!query.exec())
	{
		throw QString(query.lastError().text()); // remove error
	}
    for (int i = 0; i < mMembers.size(); ++i)
    {
        if (mMembers[i].id == member.id)
        {
            mMembers[i] = member;
            break;
        }
    }
    emit memberUpdated(member);
}

Member MemberManager::getMemberByFullName(const QString& name)
{
    for (const auto& member : mMembers)
    {
        if (member.getFullName() == name) return member;
    }
    return Member();
}
