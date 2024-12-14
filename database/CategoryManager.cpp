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
    QSqlQuery query("SELECT * FROM ? OREDER BY id DESC");
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
    qDebug() << "Окончено создание менеджера категорий";
}

QMap<int, QString> CategoryManager::getCategories() const
{
    return mCategories;
}

void CategoryManager::addCategory(const QString& category)
{
    qDebug() << "Начато добавление категории " << category;
    mCategories[mCategories.keys().count()] = category;
    QSqlQuery query("INSERT INTO ? (name) VALUES (?) ");
    query.addBindValue(mTableName);
    query.addBindValue(category);
    if (!query.exec())
    {
        qDebug() << "Запрос завершился с результатом " << query.lastError().text();
    }
    else
    {
        qDebug() << "Ошибка выполнения запроса";
    }
    emit categoryAdded(category);
    qDebug() << "Окончено добавление категории";
}

void CategoryManager::removeCategory(const QString& category)
{
    qDebug() << "Начато удаление категории " << category;
    int id = mCategories.key(category);
    mCategories.remove(id);
    QSqlQuery query("DELETE FROM ? WHERE id = ?");
    query.addBindValue(mTableName);
    query.addBindValue(id);
    if (query.exec())
    {
        qDebug() << "Запрос завершился с результатом " << query.lastError().text();
    }
    else
    {
        qDebug() << "Ошибка выполнения запроса";
    }
    emit categoryRemoved(category);
    qDebug() << "Окончено удаление категории";
}

void CategoryManager::removeCategory(int categoryId)
{
    qDebug() << "Начато удаление категории " << categoryId;
    QString category = mCategories.value(categoryId);
    mCategories.remove(categoryId);
    QSqlQuery query("DELETE FROM ? WHERE id = ?");
    query.addBindValue(mTableName);
    query.addBindValue(categoryId);
    if (query.exec())
    {
        qDebug() << "Запрос завершился с результатом " << query.lastError().text();
    }
    else
    {
        qDebug() << "Ошибка выполнения запроса";
    }
    emit categoryRemoved(category);
    qDebug() << "Окончено удаление категории";
}
