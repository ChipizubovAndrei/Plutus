#pragma once

#include <QWidget>
#include <QPushButton>

#include <MoneyOperationTableModel.h>
#include <MoneyOperationTableView.h>

class AccountMoneyOperationBrowser : public QWidget
{
	Q_OBJECT

public:
	AccountMoneyOperationBrowser(QWidget *parent);

private:
	MoneyOperationTableView* mViewAccountOperationTable;
	MoneyOperationTableModel* mModelAccountOperationTable;
	QPushButton* mAddOperationButton;
	QPushButton* mRemoveOperationButton;
};
