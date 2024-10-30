#include "MoneyOperationTableModel.h"

MoneyOperationTableModel::MoneyOperationTableModel(QObject *parent)
	: QStandardItemModel(parent)
{
	setHeaderData(0, Qt::Horizontal, "Data");
	setHeaderData(1, Qt::Horizontal, "Category");
	setHeaderData(2, Qt::Horizontal, "Money");
	setHeaderData(3, Qt::Horizontal, "Note");
}

void MoneyOperationTableModel::addOperation(MoneyOperation* operation)
{
	setItem(0, 0, new QStandardItem(operation->date.toString()));
	setItem(0, 1, new QStandardItem(operation->category));
	setItem(0, 2, new QStandardItem(QString("17000")));
	setItem(0, 3, new QStandardItem(operation->note));
}
