#ifndef USERS_H
#define USERS_H

#include <QString>
#include <stdint.h>

class Users
{
public:
    Users(const uint& id, const QString& username
           , const QString& password, const uint& userType
          , const uint& workerID)
        :m_ID(id), m_Username(username), m_Password(password)
        , m_UserType(userType), m_WorkerID(workerID){};

    inline auto getID()       const { return this->m_ID;        }
    inline auto getUsername() const { return this->m_Username;  }
    inline auto getPassword() const { return this->m_Password;  }
    inline auto getUserType() const { return this->m_UserType;  }
    inline auto getWorkerID() const { return this->m_WorkerID;  }

    inline void setID(const uint& id)
    { this->m_ID = id; }
    inline void setUsername(const QString& username)
    { this->m_Username = username; }
    inline void setPassword(const QString& password)
    { this->m_Password = password; }
    inline void setUserType(const uint& userType)
    { this->m_UserType = userType; }
    inline void setWorkerID(const uint& workerID)
    { this->m_WorkerID = workerID; }

private:
    uint m_ID;
    QString m_Username;
    QString m_Password;
    uint m_UserType;
    uint m_WorkerID;
};

#endif // USERS_H
