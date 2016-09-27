#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GuiCentralWidget.h"
#include "GlobalData.h"

#include "ThreadData.h"
#include "ThreadNet.h"

#include <QApplication>
#include <QSystemTrayIcon>

#ifdef Q_OS_MAC
//#include <QtMacExtras>
#include <QtMac>
#endif

class Hive : public QObject
{
  Q_OBJECT

public:
  Hive(QObject *parent = 0);
  ~Hive();

  GuiCentralWidget *gui_central_widget;
  ThreadData *thread_data;
  ThreadNet *thread_net;

private:
  QJsonObject wrapTextMessage(const Message::TextMessageStruct &textMessageStruct);
  QJsonObject wrapFileMessage(const Message::FileInfoStruct &fileMessageStruct);

private slots:
  void onTextMessageToSend(const QString &receiver, const QString &message);

};

#endif // MAINWINDOW_H
