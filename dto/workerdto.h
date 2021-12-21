#ifndef ROLEDTO_H
#define ROLEDTO_H

#include <QString>
#include "../role.h"

class WorkerDTO
{
public:
    WorkerDTO() {};
    ~WorkerDTO() {};

    inline const auto getID()          { return this->m_ID;            }
    inline const auto getName()        { return this->m_Name;          }
    inline const auto getSurname()     { return this->m_Surname;       }
    inline const auto getPatronymic()  { return this->m_Patronymic;    }
    inline const auto getPhone()       { return this->m_Phone;         }
    inline const auto getSalary()      { return this->m_Salary;        }
    inline const auto getWarehouseID() { return this->m_WarehouseID;   }
    inline const auto getRoleID()      { return this->m_RoleID;        }

    inline void setID(const uint& id)
    { this->m_ID = id; }
    inline void setName(const QString& name)
    { this->m_Name = name; }
    inline void setSurname(const QString& surname)
    { this->m_Surname = surname; }
    inline void setPatronymic(const QString& patronymic)
    { this->m_Patronymic = patronymic; }
    inline void setPhone(const QString& phone)
    { this->m_Phone = phone; }
    inline void setSalary(const float& salary)
    { this->m_Salary = salary; }
    inline void setWarehouseID(const uint& warehouseID)
    { this->m_WarehouseID = warehouseID; }
    inline void setRoleID(const uint& roleID)
    { this->m_RoleID = roleID; }

private:
    uint m_ID;
    QString m_Name;
    QString m_Surname;
    QString m_Patronymic;
    QString m_Phone;
    float m_Salary;
    uint m_WarehouseID;
    uint m_RoleID;
};

#endif // ROLEDTO_H
