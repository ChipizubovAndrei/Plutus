#include "MoneyOperationDialog.h"

#include <QLineEdit>
#include <QDoubleValidator>
#include <QCalendarWidget>

#include <AccountManager.h>
#include <MemberManager.h>
#include <CategoryManager.h>
#include <OperationManager.h>

MoneyOperationDialog::MoneyOperationDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle("Добавить операцию по счету");

    QSharedPointer<AccountManager> accountManager = AccountManager::instance();
    QSharedPointer<CategoryManager> categoryManager = CategoryManager::instance();
    QSharedPointer<MemberManager> memberManager = MemberManager::instance();

	mDate = new QDateEdit();
	mDate->setDate(QDate::currentDate());
	mDate->setCalendarPopup(true);
	mDate->setCalendarWidget(new QCalendarWidget());

	mDstAccount = new QComboBox();
	mDstAccount->addItem("Счет не указан");
    for (auto account : accountManager->getAccounts())
    {
        mDstAccount->addItem(account.name);
    }
	mDstAccount->setCurrentIndex(0);

	mCategory = new QComboBox();
	mCategory->addItem("Нет категории");
    for (auto category : categoryManager->getCategories())
    {
        mCategory->addItem(category.name);
    }
	mCategory->setCurrentIndex(0);

    mMember = new QComboBox();
    mMember->addItem("Выберете участника");
    for (auto member : memberManager->getMembers())
    {
        mMember->addItem(member.getFullName());
    }
    mMember->setCurrentIndex(0);

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

	mLayout->addWidget(new QLabel("Категория:"), widgetIndex, 0);
	mLayout->addWidget(mCategory, widgetIndex++, 1);

    mLayout->addWidget(new QLabel("Участник:"), widgetIndex, 0);
    mLayout->addWidget(mMember, widgetIndex++, 1);

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
	QSharedPointer<AccountManager> accountManager = AccountManager::instance();
    QSharedPointer<CategoryManager> categoryManager = CategoryManager::instance();
    QSharedPointer<MemberManager> memberManager = MemberManager::instance();

    mResultMoneyOperation = MoneyOperation();
    mResultMoneyOperation.id = -1;
    mResultMoneyOperation.member_id = memberManager->getMemberByFullName(mMember->currentText()).id;
    mResultMoneyOperation.category_id = categoryManager->getCategoryByName(mCategory->currentText()).id;
    mResultMoneyOperation.date = mDate->date();
    mResultMoneyOperation.moneyAmount = static_cast<int>(mAmount->text().toDouble()*100);
    mResultMoneyOperation.note = mNote->text();

	accept();
}

MoneyOperation MoneyOperationDialog::getResult() const
{
	return mResultMoneyOperation;
}
