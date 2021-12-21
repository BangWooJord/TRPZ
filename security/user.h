#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(const uint &id, const QString &type)
        :ID(id), Type(type){}
    virtual ~User() {};

    const auto getID()   { return this->ID;         }
    const auto getType() { return this->Type;       }

private:
    uint ID;
    QString Type;
};

#endif // USER_H
