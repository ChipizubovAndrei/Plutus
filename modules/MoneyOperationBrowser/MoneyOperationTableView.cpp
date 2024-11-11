#include "MoneyOperationTableView.h"

MoneyOperationTableView::MoneyOperationTableView(QWidget *parent)
	: QTableView(parent)
{
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	hideColumn(4);
}
