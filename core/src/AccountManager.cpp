#include "AccountManager.h"

AccountManager::AccountManager(QObject *parent)
	: QObject(parent)
{}

void AccountManager::addAccount(QSharedPointer<IAccount> account)
{
	mAccounts.append(account);
	emit accountAdded(account);
}

void AccountManager::removeAccount(QSharedPointer<IAccount> account)
{
	mAccounts.removeAll(account);
}

// TODO: BE-1
QSharedPointer<IAccount> AccountManager::getAccountById(int id) const
{
	for (auto account : mAccounts)
	{
		if (account->getId() == id) return account;
	}
	return QSharedPointer<IAccount>();
}

// TODO: BE-1
QSharedPointer<IAccount> AccountManager::getAccountByName(const QString& name) const
{
	for (auto account : mAccounts)
	{
		if (account->getName() == name) return account;
	}
	return QSharedPointer<IAccount>();
}
QList<QSharedPointer<IAccount>> AccountManager::getAccounts() const
{
	return mAccounts;
}