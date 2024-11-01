#include <MockMoneyOperationManager.h>

MockMoneyOperationManager::MockMoneyOperationManager(QObject *parent)
	: IMoneyOperationManager(parent)
{}

void MockMoneyOperationManager::addMoneyOperation(MoneyOperation* operation)
{

}

void MockMoneyOperationManager::removeMoneyOperation(MoneyOperation* operation)
{

}

void MockMoneyOperationManager::loadFromDatabase()
{

}