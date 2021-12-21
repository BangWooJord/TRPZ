#ifndef ROLE_H
#define ROLE_H

#include <stdint.h>
#include <QString>

class Role
{
public:
    Role(const uint& id, const QString& name):
        m_ID(id), m_Name(name) {};

    inline auto getID()  { return this->m_ID;    }
    inline auto getName(){ return this->m_Name;  }

    inline void setID(const uint& id)       { this->m_ID = id;      }
    inline void setName(const QString& name){ this->m_Name = name;  }

private:
    uint m_ID;
    QString m_Name;
};

#endif // ROLE_H
