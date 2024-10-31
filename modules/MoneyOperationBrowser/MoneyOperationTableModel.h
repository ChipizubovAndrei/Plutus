#pragma once

#include <QStandardItemModel>

#include <MoneyOperation.h>

class MoneyOperationTableModel : public QStandardItemModel
{
	Q_OBJECT

public:
	MoneyOperationTableModel(QObject *parent=nullptr);

	void addOperation(MoneyOperation* operation);
	//void removeOperation();
};
