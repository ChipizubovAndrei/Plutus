#include "DebitAccount.h"

DebitAccount::DebitAccount(QString name, int id, int moneyAmount, QObject* parent)
	: mName(name), mId(id), mMoneyAmount(moneyAmount), IAccount(parent)
{}

QString DebitAccount::getName() const
{
	return mName;
}

void DebitAccount::setName(const QString& name)
{
	mName = name;
}

int DebitAccount::getId() const
{
	return mId;
}

void DebitAccount::setId(int id)
{
	mId = id;
}

int DebitAccount::getMoneyAmount() const
{
	return mMoneyAmount;
}

void DebitAccount::setMoneyAmount(int moneyAmount)
{
	mMoneyAmount = moneyAmount;
}

void DebitAccount::addMoney(int money)
{
	mMoneyAmount = mMoneyAmount + money;
}

void DebitAccount::reduceMoney(int money)
{
	mMoneyAmount = mMoneyAmount - money;
}
