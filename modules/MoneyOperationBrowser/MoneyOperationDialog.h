#pragma once

#include <QDialog>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>

class MoneyOperationDialog : public QDialog
{
	Q_OBJECT

public:
	MoneyOperationDialog(QWidget *parent);

private slots:
	void onAmountEditingFinished();

private:
	QDateEdit* mDate;
	QComboBox* mCategory;
	QLineEdit* mAmount;
	QLineEdit* mNote;

	QFormLayout* mLayout;
	QPushButton* mApplyButton;
	QPushButton* mCancelButton;
};
