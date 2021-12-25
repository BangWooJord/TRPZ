#ifndef CREATOR_H
#define CREATOR_H

#include "admin.h"
#include "director.h"
#include "manager.h"

class Creator{
public:
    virtual ~Creator();
    virtual User* FactoryMethod(uint id) const = 0;

};

class AdminCreator : public Creator{
public:
    Admin* FactoryMethod(uint id) const override{
        return new Admin(id);
    }
};
class DirectorCreator : public Creator{
public:
    Director* FactoryMethod(uint id) const override{
        return new Director(id);
    }
};

#endif // CREATOR_H
