#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "user.h"

class Director : public User
{
public:
    Director(const uint &id)
        :User(id, "Director") {}
    ~Director(){};

private:
    uint ID;
    QString Type;
};

#endif // DIRECTOR_H
