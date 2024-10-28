#pragma once

#include <QObject>

class UserTest : public QObject
{
	Q_OBJECT

public:
	UserTest(QObject *parent=nullptr);

private slots:
	void initTest();
	void copyConstractorTest();
};
