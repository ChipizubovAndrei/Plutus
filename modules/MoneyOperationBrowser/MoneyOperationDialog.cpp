#include "MoneyOperationDialog.h"

#include <QLineEdit>
#include <QDoubleValidator>

MoneyOperationDialog::MoneyOperationDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle("Add money operation");

	mDate = new QDateEdit();
	mDate->setDate(QDate::currentDate());
	mCategory = new QComboBox();
	mCategory->setCurrentText("NULL");
	mAmount = new QLineEdit();
	QDoubleValidator* validator = new QDoubleValidator();
	validator->setNotation(QDoubleValidator::StandardNotation);
	mAmount->setValidator(validator);
	mNote = new QLineEdit();

	mLayout = new QFormLayout(this);
	mLayout->addRow(tr("&Data:"), mDate);
	mLayout->addRow(tr("&Category:"), mCategory);
	mLayout->addRow(tr("&Amount:"), mAmount);
	mLayout->addRow(tr("&Note:"), mNote);

	mApplyButton = new QPushButton("Ok");
	mCancelButton = new QPushButton("Cancel");
	mApplyButton->setEnabled(false);
	mLayout->addWidget(mApplyButton);
	mLayout->addWidget(mCancelButton);

	connect(mAmount, &QLineEdit::textEdited, this, &MoneyOperationDialog::onAmountEditingFinished);
	connect(mApplyButton, &QPushButton::clicked, this, &QDialog::accept);
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
