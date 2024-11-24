#pragma once

#include <QObject>
#include <QString>

class IAccount : public QObject
{
	Q_OBJECT

public:
	IAccount(QObject *parent=nullptr);

	virtual QString getName() const = 0;
	virtual void setName(const QString& name) = 0;

	virtual int getId() const = 0;
	virtual void setId(int id) = 0;

	virtual int getMoneyAmount() const = 0;
	virtual void setMoneyAmount(int moneyAmount) = 0;

signals:
	void moneyAdded(int money);
	void moneyReduced(int money);

public slots:
	virtual void addMoney(int money) = 0;
	virtual void reduceMoney(int money) = 0;

};