#include <QDebug>
#include <QVariant>
#include <QtSql/QSqlQuery>

#include "rolerepo.h"
#include "workerrepo.h"
#include "../worker.h"

WorkerRepo::WorkerRepo()
{}

std::vector<int> WorkerRepo::find(const std::map<std::string, std::string> values)
{
    std::vector<int> found_id;
    QString string_query = "SELECT * FROM Workers WHERE ";
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

std::vector<Worker> WorkerRepo::getAll()
{
    std::vector<Worker> item_list;

    QSqlQuery query;
    query.exec("SELECT * FROM Workers");
    while(query.next()){
        item_list.push_back(Worker(query.value("ID").toUInt()
                                   ,query.value("Name").toString()
                                   ,query.value("Surname").toString()
                                   ,query.value("Patronymic").toString()
                                   ,query.value("Phone").toString()
                                   ,query.value("Salary").toFloat()
                                   ,query.value("WarehouseID").toUInt()
                                   ,query.value("Role").toUInt()));
    }

    return item_list;
}

Worker* WorkerRepo::get(int id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM Workers WHERE ID=%1").arg(id));
    query.first();
    return (query.isValid())
               ? new Worker(query.value("ID").toUInt()
                            ,query.value("Name").toString()
                            ,query.value("Surname").toString()
                            ,query.value("Patronymic").toString()
                            ,query.value("Phone").toString()
                            ,query.value("Salary").toFloat()
                            ,query.value("WarehouseID").toUInt()
                            ,query.value("Role").toUInt())
               : nullptr;
}

void WorkerRepo::Create(Worker item)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO Workers (ID, Name, Surname, Patronymic"
                       ",Phone, Salary, WarehouseID, Role) VALUES "
                       "(%1, '%2', '%3', '%4', '%5', %6, %7, %8)")
                   .arg(item.getID()).arg(item.getName())
                   .arg(item.getSurname()).arg(item.getPatronymic())
                   .arg(item.getPhone()).arg(item.getSalary())
                   .arg(item.getWarehouseID()).arg(item.getRoleID()));
}

void WorkerRepo::Update(Worker item)
{
    if(!get(item.getID())) return;
    QSqlQuery query;
    query.exec(QString("UPDATE Workers SET Name='%1', Surname='%2'"
                       ", Patronymic='%3', Phone='%4'"
                       ", Salary=%5, WarehouseID=%6"
                       ", Role=%7 WHERE ID=%8").arg(item.getName())
                        .arg(item.getSurname()).arg(item.getPatronymic())
                        .arg(item.getPhone()).arg(item.getSalary())
                        .arg(item.getWarehouseID()).arg(item.getRoleID())
                        .arg(item.getID()));
}

void WorkerRepo::Delete(int id)
{
    if(!get(id)) return;
    QSqlQuery query;
    query.exec(QString("DELETE FROM Workers WHERE ID=%1").arg(id));
}
