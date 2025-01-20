#include "MoneyOperationDialog.h"

#include <QLineEdit>
#include <QDoubleValidator>
#include <QCalendarWidget>

#include <AccountManager.h>

MoneyOperationDialog::MoneyOperationDialog(QWidget *parent, Type type)
	: QDialog(parent), mType(type)
{
	setWindowTitle("Добавить операцию по счету");

	mDate = new QDateEdit();
	mDate->setDate(QDate::currentDate());
	mDate->setCalendarPopup(true);
	mDate->setCalendarWidget(new QCalendarWidget());

	mDstAccount = new QComboBox();
	mDstAccount->addItem("Счет не указан");
	mDstAccount->setCurrentIndex(0);

	if (mType == Type::Inner)
	{
		mSrcAccount = new QComboBox();
		mSrcAccount->addItem("Счет не указан");
		mSrcAccount->setCurrentIndex(0);
	}

	mCategory = new QComboBox();
	mCategory->addItem("Нет категории");
	mCategory->setCurrentIndex(0);

	mAmount = new QLineEdit();
	QDoubleValidator* validator = new QDoubleValidator();
	validator->setNotation(QDoubleValidator::StandardNotation);
	mAmount->setValidator(validator);

	mNote = new QLineEdit();

	int widgetIndex = 0;
	mLayout = new QGridLayout(this);
	mLayout->addWidget(new QLabel("Дата:"), widgetIndex, 0);
	mLayout->addWidget(mDate, widgetIndex++, 1);

	mLayout->addWidget(new QLabel("Целевой счет:"), widgetIndex, 0);
	mLayout->addWidget(mDstAccount, widgetIndex++, 1);

	if (mType == Type::Inner)
	{
		mLayout->addWidget(new QLabel("Счет источник:"), widgetIndex, 0);
		mLayout->addWidget(mSrcAccount, widgetIndex++, 1);
	}

	mLayout->addWidget(new QLabel("Категория:"), widgetIndex, 0);
	mLayout->addWidget(mCategory, widgetIndex++, 1);

	mLayout->addWidget(new QLabel("Сумма:"), widgetIndex, 0);
	mLayout->addWidget(mAmount, widgetIndex++, 1);

	mLayout->addWidget(new QLabel("Заметка:"), widgetIndex, 0);
	mLayout->addWidget(mNote, widgetIndex++, 1);


	mApplyButton = new QPushButton("Ок");
	mCancelButton = new QPushButton("Отмена");
	mApplyButton->setEnabled(false);

	QHBoxLayout* btnLayout = new QHBoxLayout();
	btnLayout->addWidget(mApplyButton);
	btnLayout->addWidget(mCancelButton);
	mLayout->addLayout(btnLayout, widgetIndex++, 0, -1, -1);

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

void MoneyOperationDialog::onAccept()
{
	QSharedPointer<AccountManager> accountManager = QSharedPointer<AccountManager>(new AccountManager());
	if (mType == Type::Outer)
	{
		mResultMoneyOperation = MoneyOperation{
			mDate->date(),
			accountManager->getAccountByName(mDstAccount->currentText()).id,
			NULL,
			mMember->currentText(),
			mCategory->currentText(),
			mAmount->text().toDouble(),
			mNote->text()
		};
	}
	else 
	{
		mResultMoneyOperation = MoneyOperation{
			mDate->date(),
			accountManager->getAccountByName(mDstAccount->currentText()).id,
			accountManager->getAccountByName(mSrcAccount->currentText()).id,
			mMember->currentText(),
			mCategory->currentText(),
			mAmount->text().toDouble(),
			mNote->text()
		};
	}

	accept();
}

MoneyOperation MoneyOperationDialog::getMoneyOperation() const
{
	return mResultMoneyOperation;
}
