#ifndef REPODB_H
#define REPODB_H

#include <QObject>

class RoleRepo;
class WorkerRepo;
class WarehouseRepo;
class UserRepo;

class RepoDB : public QObject
{
    Q_OBJECT
public:
    ~RepoDB();
    RepoDB(RepoDB& copy) = delete;
    void operator=(const RepoDB&) = delete;

    static RepoDB* getInstance();

    const auto roleRepo()       { return this->m_roleRepo;      }
    const auto workerRepo()     { return this->m_workerRepo;    }
    const auto warehouseRepo()  { return this->m_warehouseRepo; }
    const auto userRepo()       { return this->m_userRepo;      }

    Q_INVOKABLE void authUser(const QString& username, const QString& pass);

signals:
    void authAccepted();
    void authDenied();

private:
    RepoDB();

    static RepoDB* instance;

    RoleRepo *m_roleRepo;
    WorkerRepo *m_workerRepo;
    WarehouseRepo *m_warehouseRepo;
    UserRepo *m_userRepo;
};

#endif // REPODB_H
