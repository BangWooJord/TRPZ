#ifndef WORKERREPO_H
#define WORKERREPO_H

#include "baserepo.h"

class Worker;
class RepoDB;

class WorkerRepo : public BaseRepo<Worker>
{
public:
    WorkerRepo(RepoDB* parent = nullptr);
    std::vector<int> find(const std::map<std::string, std::string> values) override;
    std::vector<Worker> getAll() override;
    Worker* get(int id) override;
    void Create(Worker item) override;
    void Update(Worker item) override;
    void Delete(int id) override;

private:
    RepoDB* m_parent;
};

#endif // WORKERREPO_H
