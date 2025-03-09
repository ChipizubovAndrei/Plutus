#include "MoneyOperationTableModel.h"

#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

#include <DatabaseManager.h>
#include <AccountManager.h>
#include <MemberManager.h>
#include <CategoryManager.h>

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
        if (index.column() == 0) // участник
        {
            return value.toString(); 
        }
        if (index.column() == 1) // категория
        {
            return value.toString();
        }
        if (index.column() == 2) // счет
        {
            return AccountManager::instance()->getAccountById(value.toInt()).name;
            //return value.toString(); 
        }
        if (index.column() == 3) // дата
        {
            return value.toString();
        }
        if (index.column() == 4) // сумма
        {
            return QString("%1").arg(value.toDouble()/100, 0, 'f', 2);
        }
        if (index.column() == 5) return value.toString(); // комментарий
    default:
        return QVariant();
    }
 
    return QVariant();
}

void MoneyOperationTableModel::refresh()
{
    setQuery(QString(
        "SELECT member_id, category_id, srcAccount_id, date, moneyAmount, note FROM %1 ORDER BY id ASC"
    ).arg(mTableName));

    int headerIndex = 0;
    setHeaderData(headerIndex++, Qt::Horizontal, "Участник");
    setHeaderData(headerIndex++, Qt::Horizontal, "Категория");
    setHeaderData(headerIndex++, Qt::Horizontal, "Счет");
    setHeaderData(headerIndex++, Qt::Horizontal, "Дата");
    setHeaderData(headerIndex++, Qt::Horizontal, "Сумма");
    setHeaderData(headerIndex++, Qt::Horizontal, "Комментарий");

}
