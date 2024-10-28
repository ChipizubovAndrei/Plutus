#pragma once

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include <IAccount.h>

class AccountManager : public QObject
{
	Q_OBJECT

public:
	AccountManager(QObject *parent);
	void addAccount(QSharedPointer<IAccount> account);
	void removeAccount(QSharedPointer<IAccount> account);
	QSharedPointer<IAccount> getAccountById(int id) const;
	QSharedPointer<IAccount> getAccountByName(const QString& name) const;

signals:
	void accountAdded(QSharedPointer<IAccount> account);
	void accountRemoved(QSharedPointer<IAccount> account);

private:
	QList<QSharedPointer<IAccount>> mAccounts;
};
