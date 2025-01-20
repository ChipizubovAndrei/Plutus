#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>

class DatabaseManager : public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<DatabaseManager> instance();
	static QDir getDatabaseDir();
	static QString getMemberTableName();
	static QString getAccountTableName();
	static QString getCategoryTableName();
	static QString getOperationTableName();

	QSqlDatabase getDatabase() const;
    bool isConnectedToDatabase() const;
    bool connectToDatabase();

private:
	DatabaseManager(QObject *parent=nullptr);
	DatabaseManager(const DatabaseManager& manager);
	DatabaseManager& operator=(const DatabaseManager& manager);

	void createTables();

private:
	QSqlDatabase mDatabase;
};
