#pragma once

#include <QDate>
#include <QString>

struct MoneyOperation
{
	QDate date;
	bool isInCome;
	QString category;
	int moneyAmount;
	QString note;
};