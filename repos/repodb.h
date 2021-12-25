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

    inline auto roleRepo()      const { return this->m_roleRepo;      }
    inline auto workerRepo()    const { return this->m_workerRepo;    }
    inline auto warehouseRepo() const { return this->m_warehouseRepo; }
    inline auto userRepo()      const { return this->m_userRepo;      }

    Q_INVOKABLE void authUser(const QString& username, const QString& pass);
    Q_INVOKABLE bool userExists(const QString& username);
    Q_INVOKABLE QString getUserRealName(const QString& username);
    Q_INVOKABLE QString getUserSurname(const QString& username);
    Q_INVOKABLE float getUserSalary(const QString& username);

    Q_INVOKABLE void createUser(const QString& username, const QString& password,
                                const int& type, const int& workerid);
    Q_INVOKABLE void createWorker(const uint& id, const QString& name
                                  , const QString& surname, const QString& patronymic
                                  , const QString& phone, const float& salary
                                  , const uint& warehouseID, const uint& roleID);
    Q_INVOKABLE int lastWorkerID();

    Q_INVOKABLE QString getRoleName(const uint& id) const;
    Q_INVOKABLE QList<QString> getAllRoleNames() const;
    Q_INVOKABLE QList<int> getAllRoleIDs() const;

    Q_INVOKABLE QList<QString> getAllWarehouseNames() const;
    Q_INVOKABLE QList<int> getAllWarehouseIDs() const;

signals:
    void authAccepted(QString username);
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
