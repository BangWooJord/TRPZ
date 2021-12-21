#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User
{
public:
    Admin(const uint &id)
        :User(id, "Admin") {}
    ~Admin(){}

private:
    uint ID;
    QString Type;
};

#endif // ADMIN_H
