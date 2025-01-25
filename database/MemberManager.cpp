#include "MemberManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include <exception>

#include "DatabaseManager.h"

MemberManager::MemberManager(QObject *parent)
	: QObject(parent),
	mMemberTableName(DatabaseManager::getMemberTableName())
{
	//get data from database
	QSqlQuery query(QString("SELECT name FROM %1 ORDER BY name ASC")
		.arg(mMemberTableName)
	);
	if (query.lastError().type() == QSqlError::NoError)
	{
		query.setForwardOnly(true);
		while (query.next())
		{
            Member member;
            member.id = query.value("id").toInt();
            member.firstName = query.value("firstName").toString();
            member.secondName = query.value("secondName").toString();
			mMembers.append(member);
		}
	}
	else
	{
		throw std::exception(); // sql query error
	}
}

QList<Member> MemberManager::getMembers() const
{
	return mMembers;
}

void MemberManager::addMember(Member member)
{
	mMembers.append(member);
    QSqlQuery query;
    query.prepare(QString("INSERT INTO :tableName (id, firstName, secondName) VALUES (:id, :firstName, :secondName)"));
    query.bindValue(":id", member.id);
    query.bindValue(":firstName", member.firstName);
    query.bindValue(":secondName", member.secondName);
    
    if (query.exec())
	{
		emit memberAdded(member);
	}
	else
	{
		throw std::exception(); // insert error
	}
}

void MemberManager::removeMember(Member member)
{
    for (int i = 0; i < mMembers.size(); ++i)
    {
        if (mMembers[i].id = member.id) mMembers.removeAt(i);
    }
    QSqlQuery query;
    query.prepare(QString("DELETE FROM :tableName WHERE id = :id"));
    query.bindValue(":tableName", mMemberTableName);
    query.bindValue(":id", member.id);
	if (query.exec())
	{
		emit memberRemoved(member);
	}
	else
	{
		throw std::exception(); // remove error
	}
}

void MemberManager::updateMember(Member member)
{
    for (int i = 0; i < mMembers.size(); ++i)
    {
        if (mMembers[i].id == member.id)
        {
            mMembers[i] = member;
            break;
        }
    }
    QSqlQuery query;
    query.prepare(QString(
        "UPDATE :tableName SET firstName = :firstName, secondName = :firstName WHERE id = :id"));
    query.bindValue(":tableName", mMemberTableName);
    query.bindValue(":firstName", member.firstName);
    query.bindValue(":secondName", member.secondName);
    query.bindValue(":id", member.id);
    query.exec();
	if (query.lastError().type() == QSqlError::NoError)
	{
		emit memberUpdated(member);
	}
	else
	{
		throw std::exception(); // remove error
	}
}

int MemberManager::getMemberIdByFullName(const QString& name)
{
    for (const auto& member : mMembers)
    {
        if (member.getFullName() == name) return member.id;
    }
    return -1;
}
