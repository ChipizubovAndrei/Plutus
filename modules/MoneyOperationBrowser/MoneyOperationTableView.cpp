#include "MoneyOperationTableView.h"

#include <QHeaderView>

MoneyOperationTableView::MoneyOperationTableView(QWidget *parent)
	: QTableView(parent)
{
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	verticalHeader()->hide();
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
