#include "repodb.h"
#include "workerrepo.h"
#include "rolerepo.h"
#include "warehouserepo.h"

RepoDB::RepoDB()
{
    m_roleRepo = new RoleRepo();
    m_workerRepo = new WorkerRepo();
    m_warehouseRepo = new WarehouseRepo();
}

RepoDB::~RepoDB()
{
}
