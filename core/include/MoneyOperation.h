#pragma once

#include <QDate>
#include <QString>

struct MoneyOperation
{
	QDate date;
	QString category;
	double moneyAmount;
	QString note;
};