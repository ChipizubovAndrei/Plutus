#pragma once

#include <QString>

struct Account
{
    int id;
    QString name;
    double moneyAmount;

    bool operator==(const Account& other) const
    {
        return id == other.id;
    }

    bool operator!=(const Account& other) const
    {
        return id != other.id;
    }
};


