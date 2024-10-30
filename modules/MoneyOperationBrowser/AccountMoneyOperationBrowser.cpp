#include "AccountMoneyOperationBrowser.h"

#include <QLayout>
#include <QTableView>

#include <MoneyOperation.h>

#include <MoneyOperationTableModel.h>
#include <MoneyOperationTableView.h>

AccountMoneyOperationBrowser::AccountMoneyOperationBrowser(QWidget *parent)
	: QWidget(parent)
{
	MoneyOperationTableModel* tableModel = new MoneyOperationTableModel();
	MoneyOperation* op = new MoneyOperation( QDate::currentDate(), true, QString("Rent"), 17000, QString("") );
	tableModel->addOperation(op);
	MoneyOperationTableView* tableView = new MoneyOperationTableView(this);
	tableView->setModel(tableModel);
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(tableView);
}
