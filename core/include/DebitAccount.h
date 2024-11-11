#pragma once

#include <IAccount.h>

class DebitAccount : public IAccount
{
	Q_OBJECT

public:
	DebitAccount(QString name, int Id, int moneyAmount, QObject* parent = nullptr);

	QString getName() const;
	void setName(const QString& name);

	int getId() const;
	void setId(int id);

	int getMoneyAmount() const;
	void setMoneyAmount(int moneyAmount);

	//QSharedPointer<IMoneyOperationManager> getMoneyOperationManager() const;
	//void setMoneyOperationManager(QSharedPointer<IMoneyOperationManager> operationManager);

public slots:
	void addMoney(int money);
	void reduceMoney(int money);

private:
	QString mName;
	int mId;
	int mMoneyAmount;
	//QSharedPointer<IMoneyOperationManager> mOperationManager;

};
