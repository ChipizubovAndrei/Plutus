﻿#pragma once

#include <QObject>
#include <QSharedPointer>

#include <Operation.h>
#include "DatabaseManager.h"

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
    void operationUpdated(MoneyOperation prevOperation,
        MoneyOperation newOperation);

private:
    OperationManager(QObject* parent = nullptr);
    OperationManager(const OperationManager& manager);
	OperationManager& operator=(const OperationManager& manager);

    int getOperationCount();

private:
    QString mOperationTableName;
    QSharedPointer<DatabaseManager> mDatabaseManager;
};
