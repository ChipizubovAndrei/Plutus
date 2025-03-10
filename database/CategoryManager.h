﻿#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QMap>

#include <Category.h>

class CategoryManager : public QObject
{
	Q_OBJECT

public:
    static QSharedPointer<CategoryManager> instance();

    QList<Category> getCategories() const;
    Category getCategoryByName( QString name ) const;
    Category getCategoryById( int id ) const;

signals:
    void categoryAdded(Category category);
    void categoryRemoved(Category category);

public slots:
    void addCategory(QString name);
    void removeCategory(Category category);
    void removeCategory(int categoryId);

private:
	CategoryManager();
	CategoryManager(const CategoryManager& manager);
	CategoryManager& operator=(const CategoryManager& manager);

private:
    QList<Category> mCategories;
    QString mCategoryTableName;
};
