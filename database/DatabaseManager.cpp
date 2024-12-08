#include "DatabaseManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include <exception>

static const QDir databaseDirName(QString("storage"));
static const QString databaseName("PlutusDB.db");
static const QString AccountTableName("Accounts");
static const QString MemberTableName("Members");
static const QString CategoryTableName("Categories");
static const QString OperationTableName("Operations");

static QSharedPointer<DatabaseManager> databaseManager;

QSharedPointer<DatabaseManager> DatabaseManager::instance()
{
	if (!databaseManager)
	{
		databaseManager = QSharedPointer<DatabaseManager>(
			new DatabaseManager()
		);
	}
	return databaseManager;
}

QString DatabaseManager::getMemberTableName()
{
	return MemberTableName;
}

QString DatabaseManager::getAccountTableName()
{
	return AccountTableName;
}

QString DatabaseManager::getCategoryTableName()
{
	return CategoryTableName;
}

QString DatabaseManager::getOperationTableName()
{
	return OperationTableName;
}

QDir DatabaseManager::getDatabaseDir()
{
	return databaseDirName;
}

DatabaseManager::DatabaseManager(QObject *parent)
	: QObject(parent)
{
	qDebug() << "Начато создание DatabaseManager";
	if (!QDir::current().exists(databaseDirName.path()))
	{
		qDebug() << "Нет папки " << databaseDirName.path() << " ,создаем";
		if (!QDir::current().mkdir(databaseDirName.path()))
		{
			qCritical() << "Не удалось создать папку";
			throw std::exception(); // database dir creation failed
		}
	}

	mDatabase = QSqlDatabase::addDatabase("QSQLITE");
	mDatabase.setDatabaseName(QString("%1%2%3")
		.arg(databaseDirName.absolutePath())
		.arg(QDir::separator())
		.arg(databaseName)
	);
	if (!mDatabase.open())
	{
        qCritical() << "Не удалось открыть файл с базой данных";
		throw std::exception(); // database open failed
	}
	// TODO: create tables ONLY when create DB
	//createTables();
	qDebug() << "Окончено создание DatabaseManager";
}

QSqlDatabase DatabaseManager::getDatabase() const
{
	return mDatabase;
}

void DatabaseManager::createTables()
{
    // Таблица не актуальна, необходимо обновить запросы!!
	if (mDatabase.isOpen())
	{
		QSqlQuery query;
		query.exec(
			QStringLiteral("CREATE TABLE %1 ("
				"id          INTEGER PRIMARY KEY AUTOINCREMENT "
				"UNIQUE NOT NULL,"
				"name        TEXT    UNIQUE "
				"NOT NULL,"
				"moneyAmount REAL    NOT NULL)")
			.arg(MemberTableName)
		);
		if (query.lastError().type() != QSqlError::NoError)
		{
			qCritical() << query.lastError().text();
			throw std::exception(); // create tables failed
		}

		query.exec(
			QStringLiteral("CREATE TABLE %1 ("
				"id          INTEGER PRIMARY KEY AUTOINCREMENT "
				"UNIQUE NOT NULL,"
				"name        TEXT    UNIQUE "
				"NOT NULL,"
				"moneyAmount REAL    NOT NULL,"
				"type        TEXT    NOT NULL "
				"DEFAULT debit")
			.arg(AccountTableName)
		);
		if (query.lastError().type() != QSqlError::NoError)
		{
			qCritical() << query.lastError().text();
			throw std::exception(); // create tables failed
		}

		query.exec(
			QStringLiteral("CREATE TABLE %1 ("
				"name TEXT PRIMARY KEY "
				"UNIQUE "
				"NOT NULL)")
			.arg(CategoryTableName)
		);
		if (query.lastError().type() != QSqlError::NoError)
		{
			qCritical() << query.lastError().text();
			throw std::exception(); // create tables failed
		}

		query.exec(
			QStringLiteral("CREATE TABLE %1 ("
				"id          INTEGER PRIMARY KEY AUTOINCREMENT "
				"UNIQUE NOT NULL,"
				"srcAccount  INTEGER REFERENCES %2 (id) ON UPDATE NO ACTION,"
				"dstAccount  INTEGER REFERENCES %2 (id),"
				"member      TEXT    REFERENCES %3 (name),"
				"category    TEXT    REFERENCES %4 (name) ON DELETE SET NULL,"
				"moneyAmount REAL    NOT NULL,"
				"note        TEXT")
			.arg(OperationTableName)
			.arg(AccountTableName)
			.arg(MemberTableName)
			.arg(CategoryTableName)
		);
		if (query.lastError().type() != QSqlError::NoError)
		{
			qCritical() << query.lastError().text();
			throw std::exception(); // create tables failed
		}
	}
}
