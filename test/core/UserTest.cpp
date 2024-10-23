#include "UserTest.h"

#include <QTest>

#include <User.h>

UserTest::UserTest(QObject *parent)
	: QObject(parent)
{}

void UserTest::initTest()
{
	User user("Andrei");
	QCOMPARE(QString("Andrei"), user.getName());
}

void UserTest::testForTest()
{
	QCOMPARE(1, 1);
}

QTEST_MAIN(UserTest)

