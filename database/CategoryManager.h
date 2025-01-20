#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QMap>

class CategoryManager : public QObject
{
	Q_OBJECT

public:
    CategoryManager();
    QMap<int, QString> getCategories() const;

signals:
    void categoryAdded(const QString& category);
    void categoryRemoved(const QString& category);

public slots:
    void addCategory(const QString& category);
    void removeCategory(const QString& category);
    void removeCategory(int categoryId);

private:
    QMap<int, QString> mCategories;
    QString mTableName;
};
