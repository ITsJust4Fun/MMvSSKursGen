#-------------------------------------------------
#
# Project created by QtCreator 2018-11-18T19:42:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MMvSSKursGen
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mmvsskursovaya.cpp \
    inputtable.cpp \
    inputnumtable.cpp \
    intensitytable.cpp \
    shortesttable.cpp \
    streamstable.cpp \
    intensitydttable.cpp \
    bandwidthtable.cpp \
    optimizationhandler.cpp \
    optimizationprogressbar.cpp

HEADERS += \
        mmvsskursovaya.h \
    inputtable.h \
    inputnumtable.h \
    intensitytable.h \
    shortesttable.h \
    streamstable.h \
    intensitydttable.h \
    bandwidthtable.h \
    optimizationhandler.h \
    optimizationprogressbar.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    kursresource.qrc
