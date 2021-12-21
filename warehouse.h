#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <stdint.h>
#include <QString>

class Warehouse
{
public:
    Warehouse(const uint& id, const QString& addr,
              const QString& city, const uint& managerID)
        :m_ID(id), m_Address(addr), m_City(city), m_ManagerID(managerID) {};

    inline const auto getID()       { return this->m_ID;        }
    inline const auto getAddress()  { return this->m_Address;   }
    inline const auto getCity()     { return this->m_City;      }
    inline const auto getManagerID(){ return this->m_ManagerID; }

    inline void setID(const uint& id)
    { this->m_ID = id; }
    inline void setAddress(const QString& addr)
    { this->m_Address = addr; }
    inline void setCity(const QString& city)
    { this->m_City = city; }
    inline void setManagerID(const uint& id)
    { this->m_ManagerID = id; }

private:
    uint m_ID;
    QString m_Address;
    QString m_City;
    uint m_ManagerID;
};

#endif // WAREHOUSE_H
