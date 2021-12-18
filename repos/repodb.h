#ifndef REPODB_H
#define REPODB_H
#include <QDebug>
class WorkerRepo;
class RoleRepo;

class RepoDB
{
public:
    RepoDB();
    ~RepoDB();

    const auto workerRepo()  { return this->m_workerRepo;    }
    const auto roleRepo()    { return this->m_roleRepo;      }
    void echo() {qDebug() << "echo";};

private:
    WorkerRepo *m_workerRepo;
    RoleRepo *m_roleRepo;
};

#endif // REPODB_H
