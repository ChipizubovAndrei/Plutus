#pragma once

#include <QObject>
#include <QSharedPointer>

#include <Operation.h>

class OperationManager : public QObject
{
	Q_OBJECT

public:
    OperationManager(QObject* parent = nullptr);

    void addOperation(const MoneyOperation& operation);
    void removeOperation(const MoneyOperation& operation);
    void updateOperation(const MoneyOperation& operation);

signals:
    void operationAdded(const MoneyOperation& operation);
    void operationRemoved(const MoneyOperation& operation);
    void operationUpdated(const MoneyOperation& operation);

private:
    QString mOperationTableName;
};
