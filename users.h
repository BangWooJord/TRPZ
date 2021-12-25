#ifndef USERS_H
#define USERS_H

#include <QString>
#include <stdint.h>

class Users
{
public:
    Users(const uint& id, const QString& username
           , const QString& password, const uint& userType)
        :m_ID(id), m_Username(username), m_Password(password)
        , m_UserType(userType){};

    inline const auto getID()       { return this->m_ID;        }
    inline const auto getUsername() { return this->m_Username;  }
    inline const auto getPassword() { return this->m_Password;  }
    inline const auto getUserType() { return this->m_UserType;  }

    inline void setID(const uint& id)
    { this->m_ID = id; }
    inline void setUsername(const QString& username)
    { this->m_Username = username; }
    inline void setPassword(const QString& password)
    { this->m_Password = password; }
    inline void setUserType(const uint& userType)
    { this->m_UserType = userType; }

private:
    uint m_ID;
    QString m_Username;
    QString m_Password;
    uint m_UserType;
};

#endif // USERS_H
