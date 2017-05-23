#-------------------------------------------------
#
# Project created by QtCreator 2017-04-18T20:11:36
#
#-------------------------------------------------

CONFIG   += c++14

QT       += core gui network widgets

macx{
    QT   += macextras

    LIBS += -L /usr/local/lib/
    INCLUDEPATH += /usr/local/include/
}


TARGET = Hive!
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    hive.cpp \
    log.cpp \
    global_variable.cpp \
    app_data_manager.cpp

HEADERS  += \
    hive.h \
    log.h \
    global_variable.h \
    app_data_manager.h
