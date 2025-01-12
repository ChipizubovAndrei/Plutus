#include "OperationManager.h"

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
