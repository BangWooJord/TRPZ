QT -= gui
QT += testlib sql

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        tests.cpp \
        ../repos/repodb.cpp \
        ../repos/rolerepo.cpp \
        ../repos/workerrepo.cpp \
        ../repos/warehouserepo.cpp \
        ../services/workerservice.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../worker.h\
    ../role.h\
    ../warehouse.h\
    ../repos/baserepo.h \
    ../repos/repodb.h \
    ../repos/rolerepo.h \
    ../repos/workerrepo.h \
    ../repos/warehouserepo.h \
    ../services/workerservice.h \
    ../security/securitycontext.h
    ../exceptions/CustomQtExceptions.hpp
