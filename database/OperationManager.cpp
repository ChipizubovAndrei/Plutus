#include "OperationManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QString>

#include "DatabaseManager.h"

static QSharedPointer<OperationManager> operationManager;

QSharedPointer<OperationManager> OperationManager::instance()
{
    try
    {
        if (!operationManager)
        {
            operationManager = QSharedPointer<OperationManager>(
                new OperationManager()
            );
        }
        return operationManager;
    }
    catch (const QString& ex)
    {
        throw ex;
    }

}

OperationManager::OperationManager(QObject *parent)
	: QObject(parent)
{
    mOperationTableName = DatabaseManager::getOperationTableName();
    try
    {
        auto databaseManager = DatabaseManager::instance();
        if (!databaseManager->isConnected())
        {
            databaseManager->connectToDatabase();
        }
    }
    catch (const QString& ex)
    {
        throw ex;
    }
}

void OperationManager::addOperation(MoneyOperation operation)
{
    qDebug() << "start OperationManager::addOperation";
    if (!operation.isValid())
    {
        operation.id = getOperationCount() + 1;
    }
    QSqlQuery query(
        QString("INSERT INTO %1 (id, srcAccount_id, member_id, category_id, date, moneyAmount, note) VALUES (%2, %3, %4, %5, %6, %7, %8)")
        .arg(mOperationTableName)
        .arg(operation.id)
        .arg(operation.srcAccount_id)
        .arg(operation.member_id)
        .arg(operation.category_id)
        .arg(QString("'%1'").arg(operation.date.toString("dd.MM.yyyy")))
        .arg(operation.moneyAmount)
        .arg(QString("'%1'").arg(operation.note))
    );
    qDebug() << query.executedQuery();
    if (query.lastError().type() != QSqlError::NoError)
    {
        qWarning() << query.lastError().text();
        throw query.lastError().text();
    }
    emit operationAdded(operation);
}

void OperationManager::removeOperation(MoneyOperation operation)
{
    if (!operation.isValid()) return;
    QSqlQuery query(
        QString("DELETE FROM %1 WHERE id = %2")
        .arg(mOperationTableName)
        .arg(operation.id)
    );
    if (query.lastError().type() != QSqlError::NoError)
    {
        qWarning() << query.lastError().text();
        throw query.lastError().text();
    }
    emit operationRemoved(operation);
}

int OperationManager::getOperationCount()
{
    qDebug() << "start OperationManager::getOperationCount";
    QSqlQuery query(
        QString("SELECT COUNT(*) FROM %1")
        .arg(mOperationTableName)
    );
    qDebug() << query.executedQuery();
    if (query.lastError().type() != QSqlError::NoError)
    {
        qWarning() << query.lastError().text();
        throw query.lastError().text();
    }
    query.next();
    return query.value(0).toInt();
}
