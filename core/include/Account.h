#pragma once

#include <QString>

struct Account
{
    int id = -1;
    QString name = QString();
    int moneyAmount = 0;

    bool operator==(const Account& other) const
    {
        return id == other.id;
    }

    bool operator!=(const Account& other) const
    {
        return id != other.id;
    }

    bool isValid() const
    {
        return id >= 0;
    }
};


