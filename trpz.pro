QT -= gui
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        repos/repodb.cpp \
        repos/rolerepo.cpp \
        repos/warehouserepo.cpp \
        repos/workerrepo.cpp \
        services/workerservice.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dto/roledto.h \
    dto/workerdto.h \
    repos/baserepo.h \
    repos/repodb.h \
    repos/rolerepo.h \
    repos/warehouserepo.h \
    repos/workerrepo.h \
    role.h \
    security/admin.h \
    security/director.h \
    security/manager.h \
    security/securitycontext.h \
    security/user.h \
    services/workerservice.h \
    warehouse.h \
    worker.h \
    exceptions/CustomQtExceptions.hpp
