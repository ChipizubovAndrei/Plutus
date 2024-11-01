#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMap>

#include <IMoneyOperationManager.h>
#include <IAccount.h>

class MockMoneyOperationManager : public IMoneyOperationManager
{
	Q_OBJECT

public:
	MockMoneyOperationManager(QObject *parent=nullptr);

public slots:
	void addMoneyOperation(MoneyOperation* opeartion);
	void removeMoneyOperation(MoneyOperation* operation);
	void loadFromDatabase();

private:
	QMap<QSharedPointer<IAccount>, QList<MoneyOperation*>> mDatabase;

};
