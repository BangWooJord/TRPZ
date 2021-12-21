#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"

class Manager : public User
{
public:
    Manager(const uint &id)
        :User(id, "Manager") {}
    ~Manager(){}

private:
    uint ID;
    QString Type;
};

#endif // MANAGER_H
