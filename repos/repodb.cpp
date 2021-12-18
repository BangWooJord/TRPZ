#include "repodb.h"
#include "workerrepo.h"
#include "rolerepo.h"

RepoDB::RepoDB()
{
    m_roleRepo = new RoleRepo();
    m_workerRepo = new WorkerRepo(this);
}

RepoDB::~RepoDB()
{
}
