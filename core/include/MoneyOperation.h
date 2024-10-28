#pragma once

#include <QDate>
#include <QString>

/*
Структура реализует одну операцию по счету пользователя
*/
struct MoneyOperation
{
	QDate date; // Дата совершения операции
	bool isInCome; // Вид операции (доход/расход)
	QString category; // Категория (аренда, з/п и т.д.)
	int moneyAmount;
	QString note; // Комментарии пользователя
};