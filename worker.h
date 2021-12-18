#ifndef WORKER_H
#define WORKER_H

#include "role.h"

class Worker
{
public:
    Worker(const uint& id, const QString& name
           , const QString& surname, const QString& patronymic
           , const QString& phone, const float& salary
           , const uint& warehouseID, const Role& role)
        :m_ID(id), m_Name(name), m_Surname(surname)
        , m_Patronymic(patronymic), m_Phone(phone)
        , m_Salary(salary), m_WarehouseID(warehouseID)
        , m_role(role){};

    inline const auto getID()          { return this->m_ID;            }
    inline const auto getName()        { return this->m_Name;          }
    inline const auto getSurname()     { return this->m_Surname;       }
    inline const auto getPatronymic()  { return this->m_Patronymic;    }
    inline const auto getPhone()       { return this->m_Phone;         }
    inline const auto getSalary()      { return this->m_Salary;        }
    inline const auto getWarehouseID() { return this->m_WarehouseID;   }
    inline const auto getRole()        { return this->m_role;          }

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
    inline void setRole(const Role& role)
        { this->m_role = role; }

private:
    uint m_ID;
    QString m_Name;
    QString m_Surname;
    QString m_Patronymic;
    QString m_Phone;
    float m_Salary;
    uint m_WarehouseID;
    Role m_role;
};

#endif // WORKER_H
