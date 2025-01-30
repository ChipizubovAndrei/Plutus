#pragma once

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include <Account.h>

class AccountManager : public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<AccountManager> instance();

	void addAccount(Account account);
	void removeAccount(Account account);
	QList<Account> getAccounts() const;
	Account getAccountById(int id) const;
	Account getAccountByName(const QString& name) const;

signals:
	void accountAdded(Account account);
	void accountRemoved(Account account);

private:
	AccountManager(QObject *parent=nullptr);
	AccountManager(const AccountManager& manager);
	AccountManager& operator=(const AccountManager& manager);

private:
	QList<Account> mAccounts;
	QString mAccountTableName;
};
