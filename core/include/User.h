#pragma once

#include <QObject>
#include <QString>

#include <AccountManager.h>

class User : public QObject
{
	Q_OBJECT

public:
	User(QString name, QObject* parent = nullptr);

	QString getName() const;
	void setName(const QString & name);

	QSharedPointer<AccountManager> getAcountManager() const;
	void setAccountManager(QSharedPointer<AccountManager> accountManager);

private:
	QString mName;
	QSharedPointer<AccountManager> mAccountManager;
};
