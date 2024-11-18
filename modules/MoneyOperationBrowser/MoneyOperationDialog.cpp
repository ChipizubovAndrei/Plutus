#include "MoneyOperationDialog.h"

#include <QLineEdit>
#include <QDoubleValidator>
#include <QCalendarWidget>

MoneyOperationDialog::MoneyOperationDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle("Add money operation");

	mDate = new QDateEdit();
	mDate->setDate(QDate::currentDate());
	mDate->setCalendarPopup(true);
	mDate->setCalendarWidget(new QCalendarWidget());

	mCategory = new QComboBox();
	mCategory->addItem("No category");
	mCategory->setCurrentIndex(0);

	mAmount = new QLineEdit();
	QDoubleValidator* validator = new QDoubleValidator();
	validator->setNotation(QDoubleValidator::StandardNotation);
	mAmount->setValidator(validator);

	mNote = new QLineEdit();

	mLayout = new QGridLayout(this);
	mLayout->addWidget(new QLabel("Date:"), 0, 0);
	mLayout->addWidget(mDate, 0, 1);

	mLayout->addWidget(new QLabel("Category:"), 1, 0);
	mLayout->addWidget(mCategory, 1, 1);

	mLayout->addWidget(new QLabel("Amount:"), 2, 0);
	mLayout->addWidget(mAmount, 2, 1);

	mLayout->addWidget(new QLabel("Note:"), 3, 0);
	mLayout->addWidget(mNote, 3, 1);


	mApplyButton = new QPushButton("Ok");
	mCancelButton = new QPushButton("Cancel");
	mApplyButton->setEnabled(false);

	QHBoxLayout* btnLayout = new QHBoxLayout();
	btnLayout->addWidget(mApplyButton);
	btnLayout->addWidget(mCancelButton);
	mLayout->addLayout(btnLayout, 4, 0, -1, -1);

	connect(mAmount, &QLineEdit::textEdited, this, &MoneyOperationDialog::onAmountEditingFinished);
	connect(mApplyButton, &QPushButton::clicked, this, &MoneyOperationDialog::onAccept);
	connect(mCancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void MoneyOperationDialog::onAmountEditingFinished()
{
	if (mAmount->hasAcceptableInput())
	{
		mApplyButton->setEnabled(true);
	}
	else
	{
		mApplyButton->setEnabled(false);
	}
}

/*
	QDate date;
	MoneyOperationType type;
	QString category;
	int moneyAmount;
	QString note;
*/

void MoneyOperationDialog::onAccept()
{
	mResultMoneyOperation = MoneyOperation{
		mDate->date(),
		mCategory->currentText(),
		mAmount->text().toDouble(),
		mNote->text()
	};
	accept();
}

MoneyOperation MoneyOperationDialog::getMoneyOperation() const
{
	return mResultMoneyOperation;
}
