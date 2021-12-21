#ifndef SECURITYCONTEXT_H
#define SECURITYCONTEXT_H

#include "user.h"


class SecurityContext
{
public:
    SecurityContext(){};
    ~SecurityContext(){};

    inline static auto getUser()            { return m_user;  }
    inline static void setUser(User& user)  { m_user = &user; }
private:
    inline static User* m_user = nullptr;
};


#endif // SECURITYCONTEXT_H
