#pragma once

#include <QString>

struct Member
{
    int id;
    QString firstName;
    QString secondName;

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
};
