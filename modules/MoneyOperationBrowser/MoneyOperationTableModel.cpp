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
        // Какие либо преобразования с данными
        // Например преобразование значений к определенному виду
        if (index.column() == 0) return value.toString(); // ID операции
        if (index.column() == 1) return value.toString(); // source account id
        if (index.column() == 2) return value.toString(); // destination account id
        if (index.column() == 3) return value.toString(); // memder id
        if (index.column() == 4) return value.toString(); // category id
        if (index.column() == 5)
        {
            // Дата совершения операции, храниться как юлианская дата
            return QDate::fromJulianDay(value.toInt()).toString("dd.mm.yyyy");
        }
        if (index.column() == 6)
        {
            // Сумма денег в операции
            return QString("%1").arg(value.toDouble(), 0, 'f', 2);
        }
        if (index.column() == 7) return value.toString(); // note
    default:
        return QVariant();
    }
 
    return QVariant();
}

bool MoneyOperationTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int column = 0;
    if (column < 1) return false;
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = QSqlQueryModel::data(primaryKeyIndex).toInt();

    QSqlQuery query;
    if (column == 1)
    {
        query.prepare("UPDATE ? SET srcAccount_id = ? WHERE id = ?");
        query.addBindValue(mTableName);
        query.addBindValue(value.toInt());
        query.addBindValue(id);

    }
    else if (column == 2)
    {
        query.prepare("UPDATE ? SET dstAccount_id = ? WHERE id = ?");
        query.addBindValue(mTableName);
        query.addBindValue(value.toInt());
        query.addBindValue(id);
    }
    else if (column == 3)
    {
        query.prepare("UPDATE ? SET member_id = ? WHERE id = ?");
        query.addBindValue(mTableName);
        query.addBindValue(value.toInt());
        query.addBindValue(id);
    }
    else if (column == 4)
    {
        query.prepare("UPDATE ? SET category_id = ? WHERE id = ?");
        query.addBindValue(mTableName);
        query.addBindValue(value.toInt());
        query.addBindValue(id);
    }
    else if (column == 5)
    {
        query.prepare("UPDATE ? SET date = ? WHERE id = ?");
        query.addBindValue(mTableName);
        query.addBindValue(value.toDate().toJulianDay());
        query.addBindValue(id);
    }
    else if (column == 6)
    {
        query.prepare("UPDATE ? SET moneyAmount = ? WHERE id = ?");
        query.addBindValue(mTableName);
        query.addBindValue(value.toDouble());
        query.addBindValue(id);
    }
    else if (column == 7)
    {
        query.prepare("UPDATE ? SET note = ? WHERE id = ?");
        query.addBindValue(mTableName);
        query.addBindValue(value.toString());
        query.addBindValue(id);
    }
    bool ok = query.exec();
    qDebug() << "Изменение данных в таблице Operations завершилось со статусом: "
             << query.lastError().text();
    refresh();
    return ok;

}

void MoneyOperationTableModel::refresh()
{
    setQuery(QString("SELECT * FROM %1 ORDER BY id DESC").arg(mTableName));

    setHeaderData(0, Qt::Horizontal, "id");
    setHeaderData(1, Qt::Horizontal, "srcAccount_id");
    setHeaderData(2, Qt::Horizontal, "dstAccount_id");
    setHeaderData(3, Qt::Horizontal, "member_id");
    setHeaderData(4, Qt::Horizontal, "category_id");
    setHeaderData(5, Qt::Horizontal, "date");
    setHeaderData(6, Qt::Horizontal, "moneyAmount");
    setHeaderData(7, Qt::Horizontal, "note");

}
