#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QSqlDatabase>
#include <QSqlTableModel>

#include "MoneyOperationTableView.h"
#include "MoneyOperationTableModel.h"

class AccountMoneyOperationBrowser : public QWidget
{
	Q_OBJECT

public:
	AccountMoneyOperationBrowser(QWidget *parent);

private slots:
	void onAddedButtonClicked();
	void onRemoveButtonClicked();

private:
	MoneyOperationTableView* mViewAccountOperationTable;
    QSharedPointer<MoneyOperationTableModel> mModelAccountOperationTable;
    //QSharedPointer<QSqlTableModel> mModelAccountOperationTable;

	QPushButton* mAddOperationButton;
	QPushButton* mRemoveOperationButton;
	QHBoxLayout* mHLayout;
	QVBoxLayout* mVLayout;

	QSqlDatabase mDatabase;
};
