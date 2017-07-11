#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T18:40:32
#
#-------------------------------------------------

QT       += core
QT	 += gui
QT	 += network
QT	 += opengl
#QT       += concurrent

CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx{
    QT   += macextras

    INCLUDEPATH += /usr/local/include/
    QMAKE_LFLAGS += -L/usr/local/lib -luv

}

win32{
    RC_FILE = /Src/hive.rc
}

TARGET = Hive!
TEMPLATE = app

SOURCES += \
    main.cpp \
    Hive.cpp \
    GlobalData.cpp \
    GlobalType.cpp \
    UsrData.cpp \
\
    Gui/CentralWidget.cpp \
    Gui/TabBlock.cpp \
    Gui/HomeTab.cpp \
    Gui/MainBlock.cpp \
    Gui/ChatTab.cpp \
    Gui/ChatStack.cpp \
    Gui/SettingsTab.cpp \
    Gui/SettingsStack_messaging.cpp \
    Gui/SettingsStack_profile.cpp \
    Gui/SettingsStack_questions.cpp \
    Gui/SettingsStack_update.cpp \
    Gui/HomeStack_storage.cpp \
    Gui/HomeStack_network.cpp \
    Gui/HomeStack_list.cpp \
    Gui/HomeStack_welcome.cpp \
\
    Gui/Frameworks/CombWidget.cpp \
    Gui/Frameworks/ScrollStack.cpp \
    Gui/Frameworks/MenuButton.cpp \
\
    Gui/Frameworks/Widgets/TextBubble.cpp \
    Gui/Frameworks/Widgets/LabelButton.cpp \
    Gui/Frameworks/Widgets/ColorPicker.cpp \
    Gui/Frameworks/Widgets/BadgeIcon.cpp \
\
    Network/NetworkManager.cpp \
\
    Data/DataManager.cpp \
    Gui/Frameworks/Widgets/AvatarWidgets.cpp \
    Log.cpp \
    UvTcpServer.cpp \
    HiveProtocol.cpp
\

HEADERS  += \
    Hive.h \
    GlobalData.h \
    GlobalType.h \
    UsrData.h \
\
    Gui/CentralWidget.h \
    Gui/TabBlock.h \
    Gui/HomeTab.h \
    Gui/MainBlock.h \
    Gui/ChatTab.h \
    Gui/ChatStack.h \
    Gui/SettingsTab.h \
    Gui/SettingsStack_messaging.h \
    Gui/SettingsStack_profile.h \
    Gui/SettingsStack_questions.h \
    Gui/SettingsStack_update.h \
    Gui/HomeStack_storage.h \
    Gui/HomeStack_network.h \
    Gui/HomeStack_list.h \
    Gui/HomeStack_welcome.h \
\
    Gui/Frameworks/CombWidget.h \
    Gui/Frameworks/ScrollStack.h \
    Gui/Frameworks/MenuButton.h \
\
    Gui/Frameworks/Widgets/TextBubble.h \
    Gui/Frameworks/Widgets/LabelButton.h \
    Gui/Frameworks/Widgets/ColorPicker.h \
    Gui/Frameworks/Widgets/BadgeIcon.h \
\
    Network/NetworkManager.h \
\
    Data/DataManager.h \
    Gui/Frameworks/Widgets/AvatarWidgets.h \
    Log.h \
    UvTcpServer.h \
    HiveProtocol.h

ICON = Src/hive.icns

RESOURCES += \
    Src/qss.qrc \
    Src/img.qrc \
    Src/font.qrc
#    Src/icon.qrc


