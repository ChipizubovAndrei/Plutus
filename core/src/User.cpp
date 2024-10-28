#include "User.h"

User::User(QString name, QObject* parent)
	: mName(name), QObject(parent)
{}

QString User::getName() const
{
	return mName;
}

void User::setName(const QString& name)
{
	mName = name;
}

QSharedPointer<AccountManager> User::getAcountManager() const
{
	return mAccountManager;
}

void User::setAccountManager(QSharedPointer<AccountManager> accountManager) 
{
	mAccountManager = accountManager;
}
