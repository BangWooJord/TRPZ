#ifndef ROLEDTO_H
#define ROLEDTO_H

#include <QString>

class RoleDTO
{
public:
    RoleDTO() {};
    ~RoleDTO();


    inline auto getID()  { return this->m_ID;    }
    inline auto getName(){ return this->m_Name;  }

    inline void setID(const uint& id)       { this->m_ID = id;      }
    inline void setName(const QString& name){ this->m_Name = name;  }

private:
    uint m_ID;
    QString m_Name;
};

#endif // ROLEDTO_H
