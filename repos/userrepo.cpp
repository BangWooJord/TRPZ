#include <QDebug>
#include <QVariant>
#include <QtSql/QSqlQuery>

#include "userrepo.h"

UserRepo::UserRepo()
{}

std::vector<int> UserRepo::find(const std::map<std::string, std::string> values)
{
    std::vector<int> found_id;
    QString string_query = "SELECT * FROM Users WHERE ";
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

std::vector<Users> UserRepo::getAll()
{
    std::vector<Users> item_list;

    QSqlQuery query;
    query.exec("SELECT * FROM Users");
    while(query.next()){
        item_list.push_back(Users(query.value("ID").toUInt()
                                   ,query.value("Username").toString()
                                   ,query.value("Password").toString()
                                   ,query.value("UserType").toUInt()));
    }

    return item_list;
}

Users* UserRepo::get(int id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM Users WHERE ID=%1").arg(id));
    query.first();
    return (query.isValid())
               ? new Users(query.value("ID").toUInt()
                    ,query.value("Username").toString()
                    ,query.value("Password").toString()
                    ,query.value("UserType").toUInt())
               : nullptr;
}

void UserRepo::Create(Users item)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO Users (ID, Username, Password, UserType)"
                       " VALUES (%1, '%2', '%3', %4)")
                   .arg(item.getID()).arg(item.getUsername())
                   .arg(item.getPassword()).arg(item.getUserType()));
}

void UserRepo::Update(Users item)
{
    if(!get(item.getID())) return;
    QSqlQuery query;
    query.exec(QString("UPDATE Users SET Username='%1', Password='%2'"
                       ", UserType=%3").arg(item.getUsername())
                   .arg(item.getPassword()).arg(item.getUserType()));
}

void UserRepo::Delete(int id)
{
    if(!get(id)) return;
    QSqlQuery query;
    query.exec(QString("DELETE FROM Users WHERE ID=%1").arg(id));
}
