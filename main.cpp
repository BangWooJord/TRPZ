#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

#include "services/workerservice.h"
#include "dto/workerdto.h"
#include "repos/repodb.h"
#include "security/securitycontext.h"
#include "security/manager.h"
#include "security/director.h"
#include "security/admin.h"
#include "exceptions/CustomQtExceptions.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase qdb = QSqlDatabase::addDatabase("QODBC3");
    qdb.setConnectOptions();
    QString connectionString = "DRIVER={ODBC Driver 17 for SQL Server};Server=localhost,54120;Database=trpz;Trusted_Connection=Yes;";
    qdb.setDatabaseName(connectionString);
    qDebug() << "Connection to database: " << qdb.open();

    RepoDB repodb;
    WorkerService* service;
    try{
        service = new WorkerService(&repodb);
    }catch(CustomQtExceptions &e){
        return 0;
    }

    User* user = new Manager(1);
    SecurityContext::setUser(*user);

    auto workers = service->getWorkers();
    if(workers.empty()) qDebug() << "No access";
    else{
        for(auto worker: workers){
            qDebug() << worker.getName();
        }
    }

    return a.exec();
}
