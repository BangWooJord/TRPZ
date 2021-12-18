#include <QDebug>
#include <QVariant>
#include <QtSql/QSqlQuery>

#include "rolerepo.h"
#include "../role.h"

RoleRepo::RoleRepo()
{
}

std::vector<int> RoleRepo::find(const std::map<std::string, std::string> values)
{
    std::vector<int> found_id;
    QString string_query = "SELECT * FROM Roles WHERE ";
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

std::vector<Role> RoleRepo::getAll()
{
    std::vector<Role> item_list;

    QSqlQuery query;
    query.exec("SELECT * FROM Roles");
    while(query.next()){
        item_list.push_back(Role(query.value(0).toUInt(), query.value(1).toString()));
    }

    return item_list;
}

Role* RoleRepo::get(int id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM Roles WHERE ID=%1").arg(id));
    query.first();
    return (query.isValid())
        ? new Role(query.value("ID").toUInt(),
                   query.value("Name").toString())
        : nullptr;
}

void RoleRepo::Create(Role item)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO Roles (ID, Name) VALUES ('%1', '%2')")
                   .arg(item.getID()).arg(item.getName()));
}

void RoleRepo::Update(Role item)
{
    if(!get(item.getID())) return;
    QSqlQuery query;
    query.exec(QString("UPDATE Roles SET Name='%1'").arg(item.getName()));
}

void RoleRepo::Delete(int id)
{
    if(!get(id)) return;
    QSqlQuery query;
    query.exec(QString("DELETE FROM Roles WHERE ID=%1").arg(id));
}
