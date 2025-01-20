#include "AccountManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseManager.h"

AccountManager::AccountManager(QObject *parent)
	: QObject(parent),
	mAccountTableName(DatabaseManager::instance()->getAccountTableName())
{
    qDebug() << "Начато создание менеджера аккаунтов";
	//get data from database
	QSqlQuery query(QString("SELECT * FROM %1 ORDER BY id ASC")
		.arg(mAccountTableName)
	);
	if (query.lastError().type() == QSqlError::NoError)
	{
		query.setForwardOnly(true);
		while (query.next())
		{
            Account account;
            account.id = query.value("id").toInt();
            account.name = query.value("name").toString();
            account.moneyAmount = query.value("moneyAmount").toDouble();
            mAccounts.append(account);
		}
	}
	else
	{
        qDebug() << "Получение данных из базы данных завершено с ошибкой "
                 << query.lastError().text();
		throw std::exception(); // sql query error
	}
    qDebug() << "Окончено создание менеджера аккаунтов";
}

void AccountManager::addAccount(Account account)
{
    qDebug() << "Начато добавление аккаунта " << account.id;
	mAccounts.append(account);
	emit accountAdded(account);
    qDebug() << "Окончено добавление аккаунта";
}

void AccountManager::removeAccount(Account account)
{
    qDebug() << "Начато удаление аккаунта " << account.name;
	mAccounts.removeAll(account);
    emit accountRemoved(account);
    qDebug() << "Окончено удаление аккаунта";
}

Account AccountManager::getAccountById(int id) const
{
	for (const auto& account : mAccounts)
	{
		if (account.id == id) return account;
	}
    qDebug() << "Аккаунт с id = " << id << " не существует";
	return Account();
}

Account AccountManager::getAccountByName(const QString& name) const
{
    qDebug() << "Получение аккаунта " << name << " по имени";
	for (const auto& account : mAccounts)
	{
		if (account.name == name) return account;
	}
	return Account();
}

QList<Account> AccountManager::getAccounts() const
{
    return mAccounts;
}
