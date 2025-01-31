#include "OperationManager.h"

#include <QSqlQuery>
#include <QString>

#include <exception>

#include "DatabaseManager.h"

static QSharedPointer<OperationManager> operationManager;

QSharedPointer<OperationManager> OperationManager::instance()
{
	if (!operationManager)
	{
		operationManager = QSharedPointer<OperationManager>(
			new OperationManager()
		);
	}
	return operationManager;
}

OperationManager::OperationManager(QObject *parent)
	: QObject(parent)
{
    mOperationTableName = DatabaseManager::getOperationTableName();

}

void OperationManager::addOperation(MoneyOperation operation)
{
    if (!operation.isValid())
    {
        operation.id = getOperationCount();
    }
    QSqlQuery query;
    query.prepare(
        QStringLiteral("INSERT INTO :tableName "
        "(id, srcAccount_id, dstAccount_id, member_id, category_id, date, moneyAmount, note) "
        "VALUES (:id, :srcAccount_id, :dstAccount_id, :member_id, :category_id, :date, :moneyAmount, :note)"
        )
    );
    query.bindValue(":tableName", mOperationTableName);
    query.bindValue(":id", operation.id);
    query.bindValue(":srcAccount_id", operation.srcAccount_id);
    query.bindValue(":dstAccount_id", operation.dstAccount_id);
    query.bindValue(":member_id", operation.member_id);
    query.bindValue(":category_id", operation.category_id);
    query.bindValue(":date", operation.date.toJulianDay());
    query.bindValue(":moneyAmount", operation.moneyAmount);
    query.bindValue(":note", operation.note);

    if (query.exec())
    {
        emit operationAdded(operation);
    }
    else
    {
        throw std::exception(); // query error
    }
}

void OperationManager::removeOperation(MoneyOperation operation)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM :tableName WHERE id = :id"));
    query.bindValue(":tableName", mOperationTableName);
    query.bindValue(":id", operation.id);
    if (query.exec())
    {
        emit operationRemoved(operation);
    }
    else
    {
        throw std::exception(); // remove error
    }
}

int OperationManager::getOperationCount()
{
    QSqlQuery query;
    query.prepare(QString("SELECT COUNT(*) AS count FROM :tableName"));
    query.bindValue(":tableName", mOperationTableName);
    if (!query.exec())
    {
        throw std::exception(); // remove error
    }
    return query.value("count").toInt();
}