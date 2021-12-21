#ifndef REPODB_H
#define REPODB_H

class WorkerRepo;
class WarehouseRepo;
class RoleRepo;

class RepoDB
{
public:
    RepoDB();
    ~RepoDB();

    const auto roleRepo()       { return this->m_roleRepo;      }
    const auto workerRepo()     { return this->m_workerRepo;    }
    const auto warehouseRepo()  { return this->m_warehouseRepo; }

private:
    RoleRepo *m_roleRepo;
    WorkerRepo *m_workerRepo;
    WarehouseRepo *m_warehouseRepo;
};

#endif // REPODB_H
