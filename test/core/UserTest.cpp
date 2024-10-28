#include "UserTest.h"

#include <QTest>
#include <QSharedPointer>

#include <User.h>

UserTest::UserTest(QObject *parent)
	: QObject(parent)
{}

void UserTest::initTest()
{
	User user("Andrei");
	QCOMPARE(QString("Andrei"), user.getName());
}

void UserTest::copyConstractorTest()
{
	QSharedPointer<User> userOriginal = QSharedPointer<User>(new User ("Andrei"));
	QSharedPointer<User> userCopy(userOriginal);
	QCOMPARE(userOriginal.data(), userCopy.data());
}

QTEST_MAIN(UserTest)

