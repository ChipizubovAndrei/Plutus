#include "CategoryManager.h"

#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseManager.h"

static QSharedPointer<CategoryManager> categoryManager;

QSharedPointer<CategoryManager> CategoryManager::instance()
{
    try
    {
	    if (!categoryManager)
	    {
		    categoryManager = QSharedPointer<CategoryManager>(
			    new CategoryManager()
		    );
	    }
	    return categoryManager;
    }
    catch (const QString& ex)
    {
        throw ex;
    }
}

CategoryManager::CategoryManager()
    : mCategoryTableName(DatabaseManager::getCategoryTableName())
{
    qDebug() << "Начато создание менеджера категорий";
    QSqlQuery query(
        QString("SELECT * FROM %1 ORDER BY id ASC").arg(mCategoryTableName)
    );
    qDebug() << query.executedQuery();
    if (query.lastError().type() == QSqlError::NoError)
    {
        Category category;
        while (query.next())
        {
            category.id = query.value("id").toInt();
            category.name = query.value("name").toString();
            mCategories.append(category);
        }
        qDebug() << QStringLiteral("Из базы данных получено %1 категорий").arg(mCategories.size());
    }
    else
    {
        qDebug() << query.lastError().text();
        throw query.lastError().text();
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
    QSqlQuery query("INSERT INTO ? (id, name) VALUES (?, ?) ");
    query.bindValue(0, mCategoryTableName);
    query.bindValue(1, category.id);
    query.bindValue(2, category.name);
    if (!query.exec())
    {
        throw query.lastError().text();
    }
    emit categoryAdded(category);
    qDebug() << "Окончено добавление категории";
}

void CategoryManager::removeCategory(Category category)
{
    qDebug() << "Начато удаление категории " << category.name;
    QSqlQuery query;
    query.prepare("DELETE FROM ? WHERE id = ?");
    query.bindValue(0, mCategoryTableName);
    query.bindValue(1, category.id);
    if (!query.exec())
    {
        throw query.lastError().text();
    }
    for (int i = 0; i < mCategories.size(); ++i)
    {
        if (mCategories[i].id = category.id) mCategories.removeAt(i);
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
    QSqlQuery query("DELETE FROM ? WHERE id = ?");
    query.bindValue(0, mCategoryTableName);
    query.bindValue(1, category.id);
    if (!query.exec())
    {
        throw query.lastError().text();
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
    qDebug() << "Категория с id = " << id << " не существует";
    return Category();
}

Category CategoryManager::getCategoryByName(QString name) const
{
    for (const auto& category : mCategories)
    {
        if (category.name == name) return category;
    }
    qDebug() << "Категория с name = " << name << " не существует";
    return Category();
}
