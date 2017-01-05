#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T18:40:32
#
#-------------------------------------------------

QT       += core gui
QT   += network
QT       += concurrent
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx{
    QT   += macextras
#    INCLUDEPATH += /usr/include
}

win32{
    RC_FILE = /Src/hive.rc
}

TARGET = Hive!
TEMPLATE = app

SOURCES += main.cpp \
    $$PWD/Gui/Frameworks/Widgets/TextBubble.cpp \
    $$PWD/Gui/Frameworks/Widgets/LabelButton.cpp \
    $$PWD/Gui/Frameworks/Widgets/AvatarButton.cpp \
    $$PWD/Gui/Frameworks/Widgets/ColorPicker.cpp \
    $$PWD/Gui/Frameworks/Widgets/BadgeIcon.cpp \
    $$PWD/Gui/Frameworks/CombWidget.cpp \
    $$PWD/Gui/Frameworks/ScrollStack.cpp \
    $$PWD/Gui/Frameworks/MenuButton.cpp \
    $$PWD/Gui/CentralWidget.cpp \
    $$PWD/Gui/TabBlock.cpp \
    $$PWD/Gui/HomeTab.cpp \
    $$PWD/Gui/MainBlock.cpp \
    $$PWD/Gui/ChatTab.cpp \
    $$PWD/Gui/ChatStack.cpp \
    $$PWD/Gui/SettingsTab.cpp \
    $$PWD/Gui/SettingsStack_messaging.cpp \
    $$PWD/Gui/SettingsStack_profile.cpp \
    $$PWD/Gui/SettingsStack_questions.cpp \
    $$PWD/Gui/SettingsStack_update.cpp \
    $$PWD/Gui/HomeStack_storage.cpp \
    $$PWD/Gui/HomeStack_network.cpp \
    $$PWD/Gui/HomeStack_list.cpp \
    $$PWD/Gui/HomeStack_welcome.cpp \
    GlobalData.cpp \
    ThreadNet.cpp \
    ThreadData.cpp \
    Hive.cpp \
    ThreadSocketTCP.cpp \
    GlobalType.cpp \
    UsrData.cpp

HEADERS  += \
    $$PWD/Gui/Frameworks/Widgets/TextBubble.h \
    $$PWD/Gui/Frameworks/Widgets/LabelButton.h \
    $$PWD/Gui/Frameworks/Widgets/AvatarButton.h \
    $$PWD/Gui/Frameworks/Widgets/ColorPicker.h \
    $$PWD/Gui/Frameworks/Widgets/BadgeIcon.h \
    $$PWD/Gui/Frameworks/CombWidget.h \
    $$PWD/Gui/Frameworks/ScrollStack.h \
    $$PWD/Gui/Frameworks/MenuButton.h \
    $$PWD/Gui/CentralWidget.h \
    $$PWD/Gui/TabBlock.h \
    $$PWD/Gui/HomeTab.h \
    $$PWD/Gui/MainBlock.h \
    $$PWD/Gui/ChatTab.h \
    $$PWD/Gui/ChatStack.h \
    $$PWD/Gui/SettingsTab.h \
    $$PWD/Gui/SettingsStack_messaging.h \
    $$PWD/Gui/SettingsStack_profile.h \
    $$PWD/Gui/SettingsStack_questions.h \
    $$PWD/Gui/SettingsStack_update.h \
    $$PWD/Gui/HomeStack_storage.h \
    $$PWD/Gui/HomeStack_network.h \
    $$PWD/Gui/HomeStack_list.h \
    $$PWD/Gui/HomeStack_welcome.h \
    GlobalData.h \
    ThreadNet.h \
    ThreadData.h \
    Hive.h \
    ThreadSocketTCP.h \
    GlobalType.h \
    UsrData.h

ICON = Src/hive.icns

RESOURCES += \
    $$PWD/Src/qss.qrc \
    $$PWD/Src/img.qrc \
    $$PWD/Src/font.qrc
#    $$PWD/Src/icon.qrc


