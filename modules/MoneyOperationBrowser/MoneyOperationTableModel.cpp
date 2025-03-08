#include "MoneyOperationTableModel.h"

#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

#include <DatabaseManager.h>

MoneyOperationTableModel::MoneyOperationTableModel()
    : mTableName(DatabaseManager::getOperationTableName())
{
    refresh();
}

QVariant MoneyOperationTableModel::data(const QModelIndex& index, int role) const
{
    QVariant value = QSqlQueryModel::data(index);

    switch(role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == 0) return value.toString();
        if (index.column() == 1) return value.toString();
        if (index.column() == 2)
        {
            auto date = QDate::fromJulianDay(value.toInt());
            qDebug() << value.toString();
            return value.toString();
        }
        if (index.column() == 3)
        {
            return QString("%1").arg(value.toDouble()/100, 0, 'f', 2);
        }
        if (index.column() == 4) return value.toString();
    default:
        return QVariant();
    }
 
    return QVariant();
}

void MoneyOperationTableModel::refresh()
{
    setQuery(QString(
        "SELECT member_id, category_id, date, moneyAmount, note FROM %1 ORDER BY id ASC"
    ).arg(mTableName));

    int headerIndex = 0;
    setHeaderData(headerIndex++, Qt::Horizontal, "member_id");
    setHeaderData(headerIndex++, Qt::Horizontal, "category_id");
    setHeaderData(headerIndex++, Qt::Horizontal, "date");
    setHeaderData(headerIndex++, Qt::Horizontal, "moneyAmount");
    setHeaderData(headerIndex++, Qt::Horizontal, "note");

}
