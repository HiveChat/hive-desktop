#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T18:40:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HiveFrame2
TEMPLATE = app

ICON = hive.icns

SOURCES += main.cpp\
        mainwindow.cpp \
    GuiCentralWidget.cpp \
    GuiTabBlock.cpp \
    GuiTabLabel.cpp \
    GuiHomeTab.cpp \
    GuiMainBlock.cpp \
    GuiChatTab.cpp \
    GuiChatStack.cpp

HEADERS  += mainwindow.h \
    GuiCentralWidget.h \
    GuiTabBlock.h \
    GuiTabLabel.h \
    GuiHomeTab.h \
    GuiMainBlock.h \
    GuiChatTab.h \
    GuiChatStack.h

RESOURCES += \
    qss.qrc \
    img.qrc
