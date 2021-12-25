#include "repodb.h"
#include "workerrepo.h"
#include "rolerepo.h"
#include "warehouserepo.h"
#include "userrepo.h"
#include "role.h"
#include "worker.h"
#include "warehouse.h"
#include "users.h"
#include <QDebug>

RepoDB* RepoDB::instance;

RepoDB::RepoDB()
{
    m_roleRepo = new RoleRepo();
    m_workerRepo = new WorkerRepo();
    m_warehouseRepo = new WarehouseRepo();
    m_userRepo = new UserRepo();
}

RepoDB::~RepoDB()
{
    delete m_roleRepo;
    delete m_workerRepo;
    delete m_warehouseRepo;
    delete m_userRepo;
}

RepoDB* RepoDB::getInstance()
{
    if(!instance) instance = new RepoDB();
    return instance;
}

void RepoDB::authUser(const QString &username, const QString &pass)
{
    const auto userIDArray = m_userRepo->find({{"Username",
                        QString("'%1'").arg(username).toStdString()}});
    if(!userIDArray.size()) emit authDenied();
    else{
        const auto userID = userIDArray[0];
        emit (m_userRepo->get(userID)->getPassword() == pass)
            ? authAccepted(username) : authDenied();
    }
}

bool RepoDB::userExists(const QString &username)
{
     return m_userRepo->find({{"Username",
                       QString("'%1'").arg(username).toStdString()}}).size();
}

QString RepoDB::getUserRealName(const QString& username)
{
    const auto userID = m_userRepo->find({{"Username",
                     QString("'%1'").arg(username).toStdString()}});
    if(!userID.size()) return "";
    else {
        const auto foundUser = m_userRepo->get(userID[0]);
        return m_workerRepo->get(foundUser->getWorkerID())->getName();
    }
}
QString RepoDB::getUserSurname(const QString& username)
{
    const auto userID = m_userRepo->find({{"Username",
                    QString("'%1'").arg(username).toStdString()}});
    if(!userID.size()) return "";
    else {
        const auto foundUser = m_userRepo->get(userID[0]);
        return m_workerRepo->get(foundUser->getWorkerID())->getSurname();
    }
}
float RepoDB::getUserSalary(const QString& username)
{
    const auto userID = m_userRepo->find({{"Username",
                    QString("'%1'").arg(username).toStdString()}});
    if(!userID.size()) return 0;
    else {
        const auto foundUser = m_userRepo->get(userID[0]);
        return m_workerRepo->get(foundUser->getWorkerID())->getSalary();
    }
}

void RepoDB::createUser(const QString &username, const QString &password,
                        const int &type, const int &workerid)
{
    m_userRepo->Create(Users(NULL, username, password, type, workerid));
}

void RepoDB::createWorker(const uint &id, const QString &name,
                          const QString &surname, const QString &patronymic,
                          const QString &phone, const float &salary,
                          const uint &warehouseID, const uint &roleID)
{
    m_workerRepo->Create(Worker(id, name, surname, patronymic,
                                phone, salary, warehouseID, roleID));
}

int RepoDB::lastWorkerID()
{
    int max = m_workerRepo->getAll()[0].getID();
    for(const auto &worker: m_workerRepo->getAll()){
        max = (max > worker.getID()) ? max : worker.getID();
    }
    return max;
}

QString RepoDB::getRoleName(const uint& id) const
{
    return m_roleRepo->get(id)->getName();
}

QList<QString> RepoDB::getAllRoleNames() const
{
    QList<QString> result;
    const auto roles = m_roleRepo->getAll();
    for(const auto &role: roles){
        result << role.getName();
    }
    return result;
}

QList<int> RepoDB::getAllRoleIDs() const
{
    QList<int> result;
    const auto roles = m_roleRepo->getAll();
    for(const auto &role: roles){
        result << role.getID();
    }
    return result;
}

QList<QString> RepoDB::getAllWarehouseNames() const
{
    QList<QString> result;
    const auto warehouses = m_warehouseRepo->getAll();
    for(const auto &warehouse: warehouses){
        result << QString("#%1, %2, %3").arg(warehouse.getID())
            .arg(warehouse.getAddress()).arg(warehouse.getCity());
    }
    return result;
}

QList<int> RepoDB::getAllWarehouseIDs() const
{
    QList<int> result;
    const auto warehouses = m_warehouseRepo->getAll();
    for(const auto &warehouse: warehouses){
        result << warehouse.getID();
    }
    return result;
}
