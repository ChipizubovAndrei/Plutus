#pragma once

#include <QDate>
#include <QString>

struct MoneyOperation
{
    int id;
	int srcAccount_id;
	int dstAccount_id;
	int member_id;
	int category_id;
    QDate date;
	double moneyAmount;
	QString note;
};
