#pragma once

#include <QDate>
#include <QString>

struct MoneyOperation
{
    int id = -1;
	int srcAccount_id = -1;
	int member_id = -1;
	int category_id = -1;
    QDate date = QDate();
	int moneyAmount = 0;
	QString note = QString("");

	bool isValid() const
	{
		return id >= 0;
	}
};
