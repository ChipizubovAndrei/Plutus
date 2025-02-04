#pragma once

#include <QString>

struct Category
{
    int id = -1;
    QString name = QString();

    bool isValid() const
    {
        return id >= 0;
    }
};
