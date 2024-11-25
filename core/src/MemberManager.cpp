#include "MemberManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include <exception>

#include "DatabaseManager.h"

static QSharedPointer<MemberManager> memberManger;

QSharedPointer<MemberManager> MemberManager::instance()
{
	if (!memberManger)
	{
		memberManger = QSharedPointer<MemberManager>(
			new MemberManager()
		);

	}
	return memberManger;

}

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
			mMembers.append(query.value(0).toString());
		}
	}
	else
	{
		throw std::exception(); // sql query error
	}
}

QList<QString> MemberManager::getMembers() const
{
	return mMembers;
}

void MemberManager::addMember(const QString& member)
{
	mMembers.append(member);
	QSqlQuery query(QString("INSERT INTO %1 name VALUES %2").arg(mMemberTableName).arg(member));
	if (query.lastError().type() == QSqlError::NoError)
	{
		emit memberAdded(member);
	}
	else
	{
		throw std::exception(); // insert error
	}
}

void MemberManager::removeMember(const QString& member)
{
	mMembers.removeAll(member);
	QSqlQuery query(QString("DELETE FROM %1 WHERE name = %2").arg(mMemberTableName).arg(member));
	if (query.lastError().type() == QSqlError::NoError)
	{
		emit memberRemoved(member);
	}
	else
	{
		throw std::exception(); // remove error
	}
}

void MemberManager::updateMember(const QString& oldMember, const QString& newMember)
{
	mMembers[mMembers.indexOf(oldMember)] = newMember;
	QSqlQuery query(QString("UPDATE %1 SET name = %2 WHERE name = %3")
		.arg(mMemberTableName)
		.arg(oldMember)
		.arg(newMember));
	if (query.lastError().type() == QSqlError::NoError)
	{
		emit memberUpdated(oldMember, newMember);
	}
	else
	{
		throw std::exception(); // remove error
	}
}

