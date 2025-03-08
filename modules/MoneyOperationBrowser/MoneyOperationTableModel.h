#pragma once

#include <QObject>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QVariant>

#include <Operation.h>

class MoneyOperationTableModel : public QSqlQueryModel
{
	Q_OBJECT

public:
	MoneyOperationTableModel();
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void refresh();

private:
    QString mTableName;
};
