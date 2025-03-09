#pragma once

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include <Account.h>
#include <Operation.h>

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

private slots:
    void onOperationAdded(const MoneyOperation& operation);
    void onOperationRemoved(const MoneyOperation& operation);
    void onOperationUpdated(const MoneyOperation& prevOperation,
        const MoneyOperation& newOperation);

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
