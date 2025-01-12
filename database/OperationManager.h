#pragma once

#include <QObject>
#include <QSharedPointer>

#include <MoneyOperation.h>

class OperationManager : public QObject
{
	Q_OBJECT

public:
    static QSharedPointer<OperationManager> instance();

    void addOperation(const MoneyOperation& operation);
    void removeOperation(const MoneyOperation& operation);
    void updateOperation(const MoneyOperation& operation);

signals:
    void operationAdded(const MoneyOperation& operation);
    void operationRemoved(const MoneyOperation& operation);
    void operationUpdated(const MoneyOperation& operation);

private:
	OperationManager(QObject *parent=nullptr);
    OperationManager(const OperationManager& other);
    OperationManager& operator=(const OperationManager& other);

private:
    QString mOperationTableName;
};
