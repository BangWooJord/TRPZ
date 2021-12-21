#include <QtTest/QtTest>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QException>
#include "../repos/repodb.h"
#include "../repos/rolerepo.h"
#include "../role.h"
#include "../repos/workerrepo.h"
#include "../services/workerservice.h"
#include "../exceptions/CustomQtExceptions.hpp"
#include "../worker.h"

class TestSQL: public QObject
{
    Q_OBJECT
private slots:
    void DBConnection()
    {
        QSqlDatabase qdb = QSqlDatabase::addDatabase("QODBC3");
        qdb.setConnectOptions();
        QString connectionString = "DRIVER={ODBC Driver 17 for SQL Server};Server=localhost,54120;Database=trpz;Trusted_Connection=Yes;";
        qdb.setDatabaseName(connectionString);
        QCOMPARE(qdb.open(), true);
    }

    void roleDB()
    {
        RoleRepo repo;
        QCOMPARE(repo.get(0)->getName(), "Office");
    }

    void workerDB()
    {
        WorkerRepo repo;
        QCOMPARE(repo.get(0)->getName(), "Alex");
    }

    void WorkerServiceConstructor()
    {
        WorkerService* service;
        try{
            service = new WorkerService(nullptr);
        }catch(CustomQtExceptions &e){
            return;
        }
        delete service;
        QFAIL("Exception was supposed to be caught");
    }
};

QTEST_MAIN(TestSQL)
#include "tests.moc"
