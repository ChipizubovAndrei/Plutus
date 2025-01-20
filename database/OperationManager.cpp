#include "OperationManager.h"

#include "DatabaseManager.h"

OperationManager::OperationManager(QObject *parent)
	: QObject(parent)
{
    mOperationTableName = DatabaseManager::getOperationTableName();

}
