#pragma once

#include <QDate>
#include <QString>

struct MoneyOperation
{
	QDate date;
	int srcAccountId;
	int dstAccountId;
	QString member;
	QString category;
	double moneyAmount;
	QString note;
};