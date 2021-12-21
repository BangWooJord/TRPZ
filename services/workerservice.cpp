#include <QDebug>
#include <QException>

#include "workerservice.h"
#include "../dto/workerdto.h"
#include "../repos/repodb.h"
#include "../worker.h"
#include "../warehouse.h"
#include "../repos/workerrepo.h"
#include "../repos/warehouserepo.h"
#include "../security/securitycontext.h"
#include "../exceptions/CustomQtExceptions.hpp"

WorkerService::WorkerService(RepoDB* db)
{
    if(db != nullptr) m_db = db;
    else throw CustomQtExceptions("NULLPTR");
}

std::vector<WorkerDTO> WorkerService::getWorkers()
{
    auto user = SecurityContext::getUser();
    std::vector<WorkerDTO> res;
    if(user == nullptr) return res;
    if(user->getType() != "Director"
        && user->getType() != "Manager")
    { return res; }

    auto manager = m_db->workerRepo()->get(user->getID());

    for(const auto& workerID: m_db->workerRepo()->find(
             {{"WarehouseID", std::to_string(manager->getWarehouseID())}}))
    {
        WorkerDTO workerDTO;
        auto worker = m_db->workerRepo()->get(workerID);

        workerDTO.setID(worker->getID());
        workerDTO.setName(worker->getName());
        workerDTO.setSurname(worker->getSurname());
        workerDTO.setPatronymic(worker->getPatronymic());
        workerDTO.setPhone(worker->getPhone());
        workerDTO.setSalary(worker->getSalary());
        workerDTO.setWarehouseID(worker->getWarehouseID());
        workerDTO.setRoleID(worker->getRoleID());

        res.push_back(workerDTO);
    }
    return res;
}
