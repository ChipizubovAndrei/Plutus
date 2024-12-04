#pragma once

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include <IAccount.h>

class AccountManager : public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<AccountManager> instance();

	void addAccount(QSharedPointer<IAccount> account);
	void removeAccount(QSharedPointer<IAccount> account);
	QList<QSharedPointer<IAccount>> getAccounts() const;
	QSharedPointer<IAccount> getAccountById(int id) const;
	QSharedPointer<IAccount> getAccountByName(const QString& name) const;

signals:
	void accountAdded(QSharedPointer<IAccount> account);
	void accountRemoved(QSharedPointer<IAccount> account);

private:
	AccountManager(QObject* parent=nullptr);
	AccountManager(const AccountManager& manager);
	AccountManager& operator=(const AccountManager& manager);

private:
	QList<QSharedPointer<IAccount>> mAccounts;
	QString mAccountTableName;
};
