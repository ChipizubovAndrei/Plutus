#include "CategoryManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include <exception>

#include "DatabaseManager.h"

CategoryManager::CategoryManager()
    : mTableName(DatabaseManager::getCategoryTableName())
{
    qDebug() << "Начато создание менеджера категорий";
    QSqlQuery query("SELECT * FROM :tableName OREDER BY id DESC");
    query.bindValue(":tableName", mTableName);
    if (query.exec())
    {
        query.setForwardOnly(true);
        while (query.next())
        {
            Category category;
            category.id = query.value("id").toInt();
            category.name = query.value("name").toString();
            mCategories.append(category);
        }
        qDebug() << QStringLiteral("Из базы данных получено %1 категорий").arg(mCategories.size());
    }
    qDebug() << "Окончено создание менеджера категорий";
}

QList<Category> CategoryManager::getCategories() const
{
    return mCategories;
}

void CategoryManager::addCategory(QString name)
{
    qDebug() << "Начато добавление категории " << name;
    Category category;
    category.id = mCategories.size();
    category.name = name;
    mCategories.append(category);
    QSqlQuery query("INSERT INTO :tableName (id, name) VALUES (:id, :name) ");
    query.bindValue(":tableName", mTableName);
    query.bindValue(":id", category.id);
    query.bindValue(":name", category.name);
    if (!query.exec())
    {
        throw std::exception(); // query error
    }
    emit categoryAdded(category);
    qDebug() << "Окончено добавление категории";
}

void CategoryManager::removeCategory(Category category)
{
    qDebug() << "Начато удаление категории " << category.name;
    for (int i = 0; i < mCategories.size(); ++i)
    {
        if (mCategories[i].id = category.id) mCategories.removeAt(i);
    }
    QSqlQuery query;
    query.prepare("DELETE FROM :tableName WHERE id = :id");
    query.bindValue(":tableName", mTableName);
    query.bindValue(":id", category.id);
    if (!query.exec())
    {
        throw std::exception(); // query error
    }
    emit categoryRemoved(category);
    qDebug() << "Окончено удаление категории";
}

void CategoryManager::removeCategory(int categoryId)
{
    qDebug() << "Начато удаление категории " << categoryId;
    Category category;
    for (int i = 0; i < mCategories.size(); ++i)
    {
        if (mCategories[i].id = categoryId)
        {
            category = mCategories[i];
            mCategories.removeAt(i);
        }
    }
    QSqlQuery query("DELETE FROM :tableName WHERE id = :id");
    query.bindValue(":tableName", mTableName);
    query.bindValue(":id", category.id);
    if (!query.exec())
    {
        throw std::exception(); // query error
    }
    emit categoryRemoved(category);
    qDebug() << "Окончено удаление категории";
}

Category CategoryManager::getCategoryById(int id) const
{
    for (const auto& category : mCategories)
    {
        if (category.id == id) return category;
    }
    qDebug() << "Аккаунт с id = " << id << " не существует";
    return Category();
}

Category CategoryManager::getCategoryByName(QString name) const
{
    for (const auto& category : mCategories)
    {
        if (category.name == name) return category;
    }
    qDebug() << "Аккаунт с name = " << name << " не существует";
    return Category();
}
