#pragma once

#include <QDate>
#include <QString>

struct MoneyOperation
{
	QDate date;
	int srcAccountId;
	int dstAccountId;
	int memberId;
	int categoryId;
	double moneyAmount;
	QString note;
};