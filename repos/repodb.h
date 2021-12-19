#ifndef REPODB_H
#define REPODB_H

class WorkerRepo;
class RoleRepo;

class RepoDB
{
public:
    RepoDB();
    ~RepoDB();

    const auto workerRepo()  { return this->m_workerRepo;    }
    const auto roleRepo()    { return this->m_roleRepo;      }

private:
    WorkerRepo *m_workerRepo;
    RoleRepo *m_roleRepo;
};

#endif // REPODB_H
