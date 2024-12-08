#include "AccountManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseManager.h"
#include <DebitAccount.h>

static QSharedPointer<AccountManager> accountManager;

QSharedPointer<AccountManager> AccountManager::instance()
{
    qDebug() << "Начато получение менеджера аккаунтов";
	if (!accountManager)
	{
        qDebug() << "Менеджера аккаунтов не существует, создаем";
		accountManager = QSharedPointer<AccountManager>(
			new AccountManager()
		);
	}
    qDebug() << "Окончено получение менеджера аккаунтов";
	return accountManager;
}

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
            // TODO. Переписать под нормальные строковые названия типов
			if (query.value(3).toInt() == 0)
			{
				QSharedPointer<IAccount> account = QSharedPointer<IAccount>(
					new DebitAccount(
						query.value(1).toString(),
						query.value(0).toInt(),
						query.value(2).toDouble()
					)
				);
				mAccounts.append(account);
			}
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

void AccountManager::addAccount(QSharedPointer<IAccount> account)
{
    qDebug() << "Начато добавление аккаунта " << account->getName();
	mAccounts.append(account);
	emit accountAdded(account);
    qDebug() << "Окончено добавление аккаунта";
}

void AccountManager::removeAccount(QSharedPointer<IAccount> account)
{
    qDebug() << "Начато удаление аккаунта " << account->getName();
	mAccounts.removeAll(account);
    emit accountRemoved(account);
    qDebug() << "Окончено удаление аккаунта";
}

QSharedPointer<IAccount> AccountManager::getAccountById(int id) const
{
	for (auto account : mAccounts)
	{
		if (account->getId() == id) return account;
	}
	return QSharedPointer<IAccount>();
}

QSharedPointer<IAccount> AccountManager::getAccountByName(const QString& name) const
{
    qDebug() << "Получение аккаунта " << name << " по имени";
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
