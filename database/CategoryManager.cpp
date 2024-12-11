#include "CategoryManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseManager.h"

static QSharedPointer<CategoryManager> categoryManager;

QSharedPointer<CategoryManager> CategoryManager::instance()
{
    if (!categoryManager)
    {
        categoryManager = QSharedPointer<CategoryManager>(new CategoryManager());
    }
    return categoryManager;
}

CategoryManager::CategoryManager()
    : mTableName(DatabaseManager::getCategoryTableName())
{
    qDebug() << "Начато создание менеджера категорий";
    QSqlQuery query("SELECT * FROM ?");
    query.addBindValue(mTableName);
    query.exec();
    qDebug() << "Получение данных завершилось со статусом " << query.lastError().text();
    if (query.lastError().type() == QSqlError::NoError)
    {
        query.setForwardOnly(true);
        while (query.next())
        {
            mCategories[query.value(0).toInt()] = query.value(1).toString();
        }
        qDebug() << QStringLiteral("Из базы данных получено %1 категорий").arg(mCategories.size());
    }
    qDebug() << "Окончено соуздание менеджера категорий";
}
