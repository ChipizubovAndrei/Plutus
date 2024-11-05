#pragma once

#include <QDate>
#include <QString>

struct MoneyOperation
{
	enum class MoneyOperationType{
		Earnings,
		Expenditure
	};

	QDate date;
	MoneyOperationType type;
	QString category;
	int moneyAmount;
	QString note;
};