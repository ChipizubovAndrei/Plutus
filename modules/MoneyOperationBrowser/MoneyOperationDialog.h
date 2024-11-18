#pragma once

#include <QDialog>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>

#include <MoneyOperation.h>

class MoneyOperationDialog : public QDialog
{
	Q_OBJECT

public:
	MoneyOperationDialog(QWidget *parent);

	MoneyOperation getMoneyOperation() const;

private slots:
	void onAmountEditingFinished();
	void onAccept();

private:
	MoneyOperation mResultMoneyOperation;

	QDateEdit* mDate;
	QComboBox* mCategory;
	QLineEdit* mAmount;
	QLineEdit* mNote;

	QGridLayout* mLayout;
	QPushButton* mApplyButton;
	QPushButton* mCancelButton;
};
