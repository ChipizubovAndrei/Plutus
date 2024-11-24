#pragma once

#include <IAccount.h>

class DebitAccount : public IAccount
{
	Q_OBJECT

public:
	DebitAccount(QString name, int Id, int moneyAmount, QObject* parent = nullptr);

	QString getName() const override;
	void setName(const QString& name) override;

	int getId() const override;
	void setId(int id) override;

	int getMoneyAmount() const override;
	void setMoneyAmount(int moneyAmount) override;

public slots:
	void addMoney(int money);
	void reduceMoney(int money);

private:
	QString mName;
	int mId;
	int mMoneyAmount;
};
