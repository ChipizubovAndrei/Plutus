#include "User.h"

User::User(QString name, QObject *parent)
	: mName(name), QObject(parent)
{}

QString User::getName()
{
	return mName;
}
