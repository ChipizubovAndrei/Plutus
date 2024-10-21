#include "UserTest.h"

#include <QTest>

#include <User.h>

UserTest::UserTest(QObject *parent)
	: QObject(parent)
{}

void UserTest::initTest()
{}

QTEST_MAIN(UserTest)

