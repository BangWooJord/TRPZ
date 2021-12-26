#ifndef USERREPO_H
#define USERREPO_H

#include "baserepo.h"
#include "../users.h"

class Users;

class UserRepo : public BaseRepo<Users>
{
public:
    enum USER_FILTERS{
        UsernameUp,
        UsernameDown,
        UserTypeUp,
        UserTypeDown
    };

    UserRepo();
    std::vector<int> find(const std::map<std::string, std::string> values) override;
    std::vector<Users> getAll() override;
    Users* get(int id) override;
    void Create(Users item) override;
    void Update(Users item) override;
    void Delete(int id) override;

    std::vector<Users> getSorted(const int& sort) override;
    QStringList getNCharsOf(const QString& target, const int& count);
};

#endif // USERREPO_H
