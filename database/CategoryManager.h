#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QMap>

#include <Category.h>

class CategoryManager : public QObject
{
	Q_OBJECT

public:
    CategoryManager();
    QList<Category> getCategories() const;

signals:
    void categoryAdded(Category category);
    void categoryRemoved(Category category);

public slots:
    void addCategory(QString name);
    void removeCategory(Category category);
    void removeCategory(int categoryId);

private:
    QList<Category> mCategories;
    QString mTableName;
};
