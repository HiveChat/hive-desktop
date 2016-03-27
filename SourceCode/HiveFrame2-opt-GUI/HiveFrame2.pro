#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T18:40:32
#
#-------------------------------------------------

QT       += core gui
QT	 += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx{
    QT	 += macextras
}


TARGET = Hive!
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
    GlobalData.cpp \
    DataHistoryIO.cpp \
    GuiOSXNotification.cpp \
    GuiMenuButton.cpp \
    GuiScrollStack.cpp \
    GuiSettingsTab.cpp \
    GuiColorPicker.cpp \
    GuiSettingsStack_messaging.cpp \
    GuiSettingsStack_profile.cpp \
    ThreadInfo.cpp \
    GuiSettingsStack_questions.cpp \
    GuiHomeStack_storage.cpp \
    ThreadNet.cpp \
    ThreadData.cpp
    #ThreadData.cpp

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
    GlobalData.h \
    DataHistoryIO.h \
    GuiOSXNotification.h \
    GuiMenuButton.h \
    GuiScrollStack.h \
    GuiSettingsTab.h \
    GuiColorPicker.h \
    GuiSettingsStack_messaging.h \
    GuiSettingsStack_profile.h \
    ThreadInfo.h \
    GuiSettingsStack_questions.h \
    GuiHomeStack_storage.h \
    ThreadNet.h \
    ThreadData.h
    #ThreadData.h

RESOURCES += \
    qss.qrc \
    img.qrc \
    font.qrc
