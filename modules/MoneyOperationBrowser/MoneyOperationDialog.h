#pragma once

#include <QDialog>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>

#include <Operation.h>

class MoneyOperationDialog : public QDialog
{
	Q_OBJECT

public:
	enum class Type
	{
		Outer = 0,
		Inner
	};

	MoneyOperationDialog(QWidget *parent, Type type = Type::Outer);

	MoneyOperation getResult() const;

private slots:
	void onAmountEditingFinished();
	void onAccept();

private:
	MoneyOperation mResultMoneyOperation;
	Type mType;

	QDateEdit* mDate;
	QComboBox* mCategory;
	QComboBox* mMember;
	QComboBox* mSrcAccount;
	QComboBox* mDstAccount;
	QLineEdit* mAmount;
	QLineEdit* mNote;

	QGridLayout* mLayout;
	QPushButton* mApplyButton;
	QPushButton* mCancelButton;
};
