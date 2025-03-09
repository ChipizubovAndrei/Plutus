#include "AccountManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseManager.h"
#include "OperationManager.h"

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
                account.moneyAmount = static_cast<int>(
                    query.value("moneyAmount").toDouble()*100);
                mAccounts.append(account);
            }

            auto operationManager = OperationManager::instance();
            connect(operationManager.data(), &OperationManager::operationAdded,
                this, &AccountManager::onOperationAdded);
            connect(operationManager.data(), &OperationManager::operationRemoved,
                this, &AccountManager::onOperationRemoved);
            connect(operationManager.data(), &OperationManager::operationUpdated,
                this, &AccountManager::onOperationUpdated);
        }
        else
        {
            qDebug() << "Получение данных из базы данных завершено с ошибкой "
                << query.lastError().text();
            throw query.lastError().text(); // sql query error
        }
    }
    catch (const QString& ex)
    {
        throw ex;
    }

    qDebug() << "Окончено создание менеджера аккаунтов";
}

void AccountManager::addAccount(Account account)
{
    qDebug() << "Начато добавление аккаунта " << account.id;
    if (!account.isValid()) account.id = mAccounts.size();
    QSqlQuery query(QString("INSERT INTO %1 (id, name, moneyAmount) VALUES (%2, %3, %4)")
        .arg(mAccountTableName)
        .arg(account.id)
        .arg(account.name)
        .arg(account.moneyAmount)
    );
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
    QSqlQuery query(QString("DELETE FROM %1 WHERE id = %2")
        .arg(mAccountTableName)
        .arg(account.id)
    );
    if (query.exec())
    {
        qWarning() << query.lastError().text();
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

void AccountManager::onOperationAdded(const MoneyOperation& operation)
{
    auto updatedAccount = getAccountById(operation.srcAccount_id);
    qDebug() << "Старый счет на аккаунте " << updatedAccount.id << " = "
        << updatedAccount.moneyAmount;
    updatedAccount.moneyAmount += operation.moneyAmount;
    qDebug() << "Новый счет на аккаунте " << updatedAccount.id << " = "
        << updatedAccount.moneyAmount;

    for (int i = 0; i < mAccounts.size(); ++i)
    {
        if (mAccounts[i].id == updatedAccount.id)
        {
            mAccounts[i] = updatedAccount;
            break;
        }
    }

    QSqlQuery query(QString("UPDATE %1 SET moneyAmount = %2 WHERE id = %3")
        .arg(mAccountTableName)
        .arg(updatedAccount.moneyAmount)
        .arg(updatedAccount.id)
    );
    if (query.lastError().type() != QSqlError::NoError)
    {
        throw query.lastError().text();
    }
}


void AccountManager::onOperationRemoved(const MoneyOperation& operation)
{

}

void AccountManager::onOperationUpdated(const MoneyOperation& prevOperation,
                        const MoneyOperation& newOperation)
{

}
