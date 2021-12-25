#include "repodb.h"
#include "workerrepo.h"
#include "rolerepo.h"
#include "warehouserepo.h"
#include "userrepo.h"

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
            ? authAccepted() : authDenied();
    }
}
