#-------------------------------------------------
#
# Project created by QtCreator 2017-04-18T20:11:36
#
#-------------------------------------------------

CONFIG   += c++14

QT       += core
QT	 += gui
QT	 += opengl
QT	 += widgets
QT	 += network

macx{
    QT   += macextras

    INCLUDEPATH += /usr/local/include/
    QMAKE_LFLAGS += -L/usr/local/lib -luv -lopencv_core

}

win32{
    RC_FILE = /Src/hive.rc
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
    global_var.cpp \
    ui/button.cpp \
    data_manager.cpp \
    _showcase.cpp

HEADERS  += \
    hive.h \
    log.h \
    global_var.h \
    ui/button.h \
    data_manager.h \
    _showcase.h

RESOURCES += \
    src/qss.qrc \
    src/img.qrc \
    src/font.qrc

ICON = src/hive.icns

