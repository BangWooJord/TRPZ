#include <QtTest/QtTest>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include "../repos/rolerepo.h"
#include "../role.h"
#include "../repos/workerrepo.h"
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

//    void workerDB()
//    {
//        WorkerRepo repo;
//        QCOMPARE(repo.get(0)->getName(), "Alex");
//    }
};

QTEST_MAIN(TestSQL)
#include "tests.moc"
