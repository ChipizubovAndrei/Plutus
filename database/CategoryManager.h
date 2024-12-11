#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QMap>

class CategoryManager : public QObject
{
	Q_OBJECT

public:
    static QSharedPointer<CategoryManager> instance();
    ~CategoryManager() = default;

signals:
    void categoryAdded(const QString& category);
    void categoryRemoved(const QString& category);

public slots:

private:
	CategoryManager();
    CategoryManager(const CategoryManager& other);
    const CategoryManager& operator=(const CategoryManager& other);

private:
    QMap<int, QString> mCategories;
    QString mTableName;
};
