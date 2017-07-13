#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GlobalData.h"
#include "Data/DataManager.h"
#include "Network/NetworkManager.h"
#include "Gui/CentralWidget.h"


#include <QApplication>
#include <QSystemTrayIcon>

#ifdef Q_OS_OSX
#include <QFileOpenEvent>
#include <QtMac>
#endif



class Hive : public QApplication
{
  Q_OBJECT

public:
  Hive(int &argc, char **argv);
  ~Hive();

  CentralWidget *gui_central_widget;
  AppDataManager *data_manager;
  NetworkManager *network_manager;

  QThread *data_thread;
  QThread *network_thread;

protected:
  bool event(QEvent* event);


//private:
//  QJsonObject wrapTextMessage(const Message::TextMessageStruct &textMessageStruct);
//  QJsonObject wrapFileMessage(const Message::FileInfoStruct &fileMessageStruct);

private slots:
  void onTextMessageToSend(const QString &receiver, const QString &message);
};

#endif // MAINWINDOW_H
