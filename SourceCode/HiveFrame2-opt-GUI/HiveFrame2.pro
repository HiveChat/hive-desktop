#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T18:40:32
#
#-------------------------------------------------

QT       += core gui
QT	 += network
QT	 += macextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HiveFrame2
TEMPLATE = app

ICON = hive.icns

SOURCES += main.cpp\
        mainwindow.cpp \
    GuiCentralWidget.cpp \
    GuiTabBlock.cpp \
    GuiHomeTab.cpp \
    GuiMainBlock.cpp \
    GuiChatTab.cpp \
    GuiChatStack.cpp \
    GuiLabelButton.cpp \
    GuiTextButton.cpp \
    GuiCombWidget.cpp \
    GuiAvatarButton.cpp \
    DataManager.cpp \
    GuiWelcomeStack.cpp \
    GuiChatBubble.cpp \
    NetManager.cpp \
    GlobalData.cpp \
    DataHistoryIO.cpp \
    GuiOSXNotification.cpp \
    GuiSettingsStack.cpp

HEADERS  += mainwindow.h \
    GuiCentralWidget.h \
    GuiTabBlock.h \
    GuiHomeTab.h \
    GuiMainBlock.h \
    GuiChatTab.h \
    GuiChatStack.h \
    GuiLabelButton.h \
    GuiTextButton.h \
    GuiCombWidget.h \
    GuiAvatarButton.h \
    DataManager.h \
    GuiWelcomeStack.h \
    GuiChatBubble.h \
    NetManager.h \
    GlobalData.h \
    DataHistoryIO.h \
    GuiOSXNotification.h \
    GuiSettingsStack.h

RESOURCES += \
    qss.qrc \
    img.qrc \
    font.qrc
