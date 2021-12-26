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
        string_query.append(QString("%1=%2 AND ").arg(key, value));
    }
    string_query.chop(5);
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
                                  ,query.value("UserType").toUInt()
                                  ,query.value("WorkerID").toUInt()));
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
                    ,query.value("UserType").toUInt()
                    ,query.value("WorkerID").toUInt())
               : nullptr;
}

void UserRepo::Create(Users item)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO Users (Username, Password, UserType, WorkerID)"
                       " VALUES ('%1', '%2', %3, %4)")
                   .arg(item.getUsername())
                   .arg(item.getPassword()).arg(item.getUserType())
                   .arg(item.getWorkerID()));
}

void UserRepo::Update(Users item)
{
    if(!get(item.getID())) return;
    QSqlQuery query;
    query.exec(QString("UPDATE Users SET Username='%1', Password='%2'"
                       ", UserType=%3, WorkerID=%4").arg(item.getUsername())
                   .arg(item.getPassword()).arg(item.getUserType())
                   .arg(item.getWorkerID()));
}

void UserRepo::Delete(int id)
{
    if(!get(id)) return;
    QSqlQuery query;
    query.exec(QString("DELETE FROM Users WHERE ID=%1").arg(id));
}

std::vector<Users> UserRepo::getSorted(const int &sort)
{
    QStringList sort_keys;
    switch (sort) {
    case USER_FILTERS::UsernameUp:
        sort_keys << "Username ASC";
        break;
    case USER_FILTERS::UsernameDown:
        sort_keys << "Username DESC";
        break;
    case USER_FILTERS::UserTypeUp:
        sort_keys << "UserType ASC";
        break;
    case USER_FILTERS::UserTypeDown:
        sort_keys << "UserType DESC";
        break;
    }

    std::vector<Users> item_list;
    QString string_query = "SELECT * FROM Users ORDER BY ";
    for(const auto& key: sort_keys){
        string_query.append(key + ",");
    }
    string_query.chop(1);
    QSqlQuery query;
    query.exec(string_query);
    while(query.next()){
        item_list.push_back(Users(query.value("ID").toUInt()
                                  ,query.value("Username").toString()
                                  ,query.value("Password").toString()
                                  ,query.value("UserType").toUInt()
                                  ,query.value("WorkerID").toUInt()));
    }
    return item_list;
}

QStringList UserRepo::getNCharsOf(const QString &target, const int& count)
{
    QStringList item_list;
    QSqlQuery query;
    query.exec(QString("SELECT LEFT(%1,%2) AS 'ANS' FROM Users").arg(target).arg(count));
    while(query.next()){
        item_list << query.value("ANS").toString();
    }
    return item_list;
}
