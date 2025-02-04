#pragma once

#include <QString>

struct Member
{
    int id = -1;
    QString firstName = QString();
    QString secondName = QString();

    bool operator==(const Member& other)
    {
        return id == other.id;
    }

    bool operator!=(const Member& other)
    {
        return id != other.id;
    }

    QString getFullName() const
    {
        return firstName + " " + secondName;
    }

    bool isValid() const
    {
        return id >= 0;
    }
};
