#pragma once

#include <QObject>
#include <QString>

class User : public QObject
{
	Q_OBJECT

public:
	User(QString name, QObject *parent=nullptr);

	QString getName();

private:
	QString mName;
};
