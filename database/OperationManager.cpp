#include "OperationManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QString>

#include <iostream>

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
	: QObject(parent), mDatabaseManager(DatabaseManager::instance())
{
    mOperationTableName = DatabaseManager::getOperationTableName();
    try
    {
        if (!mDatabaseManager->isConnected())
        {
            mDatabaseManager->connectToDatabase();
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
    mDatabaseManager->execSqlQuery(
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
    emit operationAdded(operation);
}

void OperationManager::removeOperation(MoneyOperation operation)
{
    if (!operation.isValid()) return;
    mDatabaseManager->execSqlQuery(
        QString("DELETE FROM %1 WHERE id = %2")
            .arg(mOperationTableName)
            .arg(operation.id)
    );
    emit operationRemoved(operation);
}

int OperationManager::getOperationCount()
{
    qDebug() << "start OperationManager::getOperationCount";
    auto query = mDatabaseManager->execSqlQuery(
        QString("SELECT MAX(id) FROM %1")
            .arg(mOperationTableName)
    );
    query.next();
    qDebug() << "operation coint = " << query.value(0).toInt();
    return query.value(0).toInt();
}
