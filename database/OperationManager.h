#pragma once

#include <QObject>
#include <QSharedPointer>

#include <Operation.h>

class OperationManager : public QObject
{
	Q_OBJECT

public:
    OperationManager(QObject* parent = nullptr);

    void addOperation(MoneyOperation operation);
    void removeOperation(MoneyOperation operation);
    void updateOperation(MoneyOperation operation);

signals:
    void operationAdded(MoneyOperation operation);
    void operationRemoved(MoneyOperation operation);
    void operationUpdated(MoneyOperation operation);

private:
    QString mOperationTableName;
};
