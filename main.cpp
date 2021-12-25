#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
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
    QGuiApplication a(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &a, [&](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QSqlDatabase qdb = QSqlDatabase::addDatabase("QODBC3");
    qdb.setConnectOptions();
    QString connectionString = "DRIVER={ODBC Driver 17 for SQL Server};Server=localhost,54120;Database=trpz;Trusted_Connection=Yes;";
    qdb.setDatabaseName(connectionString);
    qDebug() << "Connection to database: " << qdb.open();

    RepoDB* repodb = RepoDB::getInstance();
    WorkerService* service;
    try{
        service = new WorkerService(repodb);
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

    engine.rootContext()->setContextProperty("BackendRepo", repodb->getInstance());

    engine.load(url);
    return a.exec();
}
