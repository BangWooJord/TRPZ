#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <stdint.h>

class Worker
{
public:
    Worker(const uint& id, const QString& name
           , const QString& surname, const QString& patronymic
           , const QString& phone, const float& salary
           , const uint& warehouseID, const uint& roleID)
        :m_ID(id), m_Name(name), m_Surname(surname)
        , m_Patronymic(patronymic), m_Phone(phone)
        , m_Salary(salary), m_WarehouseID(warehouseID)
        , m_RoleID(roleID){};

    inline auto getID()          const { return this->m_ID;            }
    inline auto getName()        const { return this->m_Name;          }
    inline auto getSurname()     const { return this->m_Surname;       }
    inline auto getPatronymic()  const { return this->m_Patronymic;    }
    inline auto getPhone()       const { return this->m_Phone;         }
    inline auto getSalary()      const { return this->m_Salary;        }
    inline auto getWarehouseID() const { return this->m_WarehouseID;   }
    inline auto getRoleID()      const { return this->m_RoleID;        }

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

#endif // WORKER_H
