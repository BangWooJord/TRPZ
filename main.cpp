#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

#include "repos/repodb.h"
#include "repos/rolerepo.h"
#include "repos/workerrepo.h"
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase qdb = QSqlDatabase::addDatabase("QODBC3");
    qdb.setConnectOptions();
    QString connectionString = "DRIVER={ODBC Driver 17 for SQL Server};Server=localhost,54120;Database=trpz;Trusted_Connection=Yes;";
    qdb.setDatabaseName(connectionString);
    qDebug() << "Connection to database: " << qdb.open();


    RepoDB repodb;
    const auto managerID = repodb.roleRepo()->find({{"Name", "'Manager'"}});
    if(!managerID.size())
        return 1;
    const auto managerIDs = repodb.workerRepo()->find({{"Role", std::to_string(managerID[0])}});
    if(!managerIDs.size())
        return 1;
    const auto manager = repodb.workerRepo()->get(managerIDs[0]);
    if(!manager)
        return 1;
    qDebug() << manager->getName() << manager->getSurname() << manager->getSalary();

    return a.exec();
}
