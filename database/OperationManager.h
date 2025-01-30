#pragma once

#include <QObject>
#include <QSharedPointer>

#include <Operation.h>

class OperationManager : public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<OperationManager> instance();

    void addOperation(MoneyOperation operation);
    void removeOperation(MoneyOperation operation);
    void updateOperation(MoneyOperation operation);

signals:
    void operationAdded(MoneyOperation operation);
    void operationRemoved(MoneyOperation operation);
    void operationUpdated(MoneyOperation operation);

private:
    OperationManager(QObject* parent = nullptr);
    OperationManager(const OperationManager& manager);
	OperationManager& operator=(const OperationManager& manager);

private:
    QString mOperationTableName;
};
