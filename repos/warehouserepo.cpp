#include <QDebug>
#include <QVariant>
#include <QtSql/QSqlQuery>

#include "warehouserepo.h"
#include "../warehouse.h"

WarehouseRepo::WarehouseRepo()
{}

std::vector<int> WarehouseRepo::find(const std::map<std::string, std::string> values)
{
    std::vector<int> found_id;
    QString string_query = "SELECT * FROM Warehouses WHERE ";
    for(const auto &value_pair: values){
        QString key = QString::fromStdString(value_pair.first);
        QString value = QString::fromStdString(value_pair.second);
        string_query.append(QString("%1=%2,").arg(key, value));
    }
    string_query.chop(1);

    QSqlQuery query;
    query.exec(string_query);
    while(query.next()){
        found_id.push_back(query.value("ID").toInt());
    }
    return found_id;
}

std::vector<Warehouse> WarehouseRepo::getAll()
{
    std::vector<Warehouse> item_list;

    QSqlQuery query;
    query.exec("SELECT * FROM Warehouses");
    while(query.next()){
        item_list.push_back(Warehouse(query.value("ID").toUInt()
                                      ,query.value("Address").toString()
                                      ,query.value("City").toString()
                                      ,query.value("ManagerID").toUInt()));
    }

    return item_list;
}

Warehouse* WarehouseRepo::get(int id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM Warehouses WHERE ID=%1").arg(id));
    query.first();
    return (query.isValid())
               ? new Warehouse(query.value("ID").toUInt()
                            ,query.value("Address").toString()
                            ,query.value("City").toString()
                            ,query.value("ManagerID").toUInt())
               : nullptr;
}

void WarehouseRepo::Create(Warehouse item)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO Warehouses (ID, Address, City, ManagerID) VALUES "
                       "(%1, '%2', '%3', %4)")
                   .arg(item.getID()).arg(item.getAddress())
                   .arg(item.getCity()).arg(item.getManagerID()));
}

void WarehouseRepo::Update(Warehouse item)
{
    if(!get(item.getID())) return;
    QSqlQuery query;
    query.exec(QString("UPDATE Warehouses SET Address='%1', City='%2'"
                       ", ManagerID=%3 WHERE ID=%4").arg(item.getAddress())
                   .arg(item.getCity()).arg(item.getManagerID())
                   .arg(item.getID()));
}

void WarehouseRepo::Delete(int id)
{
    if(!get(id)) return;
    QSqlQuery query;
    query.exec(QString("DELETE FROM Warehouses WHERE ID=%1").arg(id));
}
