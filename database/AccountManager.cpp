#include "AccountManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseManager.h"

static QSharedPointer<AccountManager> accountManager;

QSharedPointer<AccountManager> AccountManager::instance()
{
    try
    {
        if (!accountManager)
        {
            accountManager = QSharedPointer<AccountManager>(
                new AccountManager()
            );
        }
        return accountManager;
    }
    catch (const QString& ex)
    {
        throw ex;
    }
}

AccountManager::AccountManager(QObject *parent)
	: QObject(parent),
	mAccountTableName(DatabaseManager::instance()->getAccountTableName())
{
    qDebug() << "Начато создание менеджера аккаунтов";
    try
    {
        auto databaseManager = DatabaseManager::instance();
        if (!databaseManager->isConnected())
        {
            databaseManager->connectToDatabase();
        }
        QSqlQuery query(QString("SELECT * FROM %1 ORDER BY id ASC")
            .arg(mAccountTableName)
        );
        if (query.lastError().type() == QSqlError::NoError)
        {
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
            throw query.lastError().text(); // sql query error
        }
    }
    catch (const std::string& ex)
    {
        throw ex;
    }

    qDebug() << "Окончено создание менеджера аккаунтов";
}

void AccountManager::addAccount(Account account)
{
    qDebug() << "Начато добавление аккаунта " << account.id;
    if (!account.isValid()) account.id = mAccounts.size();
    QSqlQuery query;
    query.prepare(QString("INSERT INTO ? (id, name, moneyAmount) VALUES (?, ?, ?)"));
    query.bindValue(0, mAccountTableName);
    query.bindValue(1, account.id);
    query.bindValue(2, account.name);
    query.bindValue(3, account.moneyAmount);
    if (!query.exec())
    {
        throw query.lastError().text();
    }
	mAccounts.append(account);
	emit accountAdded(account);
    qDebug() << "Окончено добавление аккаунта";
}

void AccountManager::removeAccount(Account account)
{
    qDebug() << "Начато удаление аккаунта " << account.name;
    QSqlQuery query;
    query.prepare("DELETE FROM ? WHERE id = ?");
    query.bindValue(0, mAccountTableName);
    query.bindValue(1, account.id);
    if (!query.exec())
    {
        throw query.lastError().text();
    }
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
