#ifndef ROLEREPO_H
#define ROLEREPO_H

#include "baserepo.h"

class Role;

class RoleRepo : public BaseRepo<Role>
{
public:
    RoleRepo();
    std::vector<int> find(const std::map<std::string, std::string> values) override;
    std::vector<Role> getAll() override;
    Role* get(int id) override;
    void Create(Role item) override;
    void Update(Role item) override;
    void Delete(int id) override;

    std::vector<Role> getSorted(const int& sort) override;
};

#endif // ROLEREPO_H
