#ifndef WORKERSERVICE_H
#define WORKERSERVICE_H

#include <vector>

class WorkerDTO;
class RepoDB;
class SecurityContext;

class WorkerService
{
public:
    WorkerService(RepoDB* db);

    std::vector<WorkerDTO> getWorkers();

private:
    RepoDB *m_db;
};

#endif // WORKERSERVICE_H
