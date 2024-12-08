#pragma once

#include <QObject>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QVariant>

#include <MoneyOperation.h>

class MoneyOperationTableModel : public QSqlQueryModel
{
	Q_OBJECT

public:
	MoneyOperationTableModel();
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role=Qt::EditRole) override;

private:
    void refresh();

private:
    QString mTableName;
};
