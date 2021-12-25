#ifndef USERREPO_H
#define USERREPO_H

#include "baserepo.h"
#include "../users.h"

class Users;

class UserRepo : public BaseRepo<Users>
{
public:
    UserRepo();
    std::vector<int> find(const std::map<std::string, std::string> values) override;
    std::vector<Users> getAll() override;
    Users* get(int id) override;
    void Create(Users item) override;
    void Update(Users item) override;
    void Delete(int id) override;
};

#endif // USERREPO_H
