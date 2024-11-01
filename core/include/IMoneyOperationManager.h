#pragma once

#include <QObject>

#include <MoneyOperation.h>

class IMoneyOperationManager : public QObject
{
	Q_OBJECT

public:
	IMoneyOperationManager(QObject *parent=nullptr);

public slots:
	virtual void addMoneyOperation(MoneyOperation* opeartion) = 0;
	virtual void removeMoneyOperation(MoneyOperation* operation) = 0;
	virtual void loadFromDatabase() = 0;
};
