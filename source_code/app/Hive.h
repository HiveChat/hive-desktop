#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Global.h"
#include "Data/AppDataManager.h"
#include "Network/NetworkManager.h"
#include "Gui/Window.h"


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

  Window *window;
  AppDataManager *data_manager;
  NetworkManager *network_manager;

//  QThread *data_thread;
  QThread *network_thread;

protected:
  bool event(QEvent* e);


//private:
//  QJsonObject wrapTextMessage(const Message::TextMessage &textMessageStruct);
//  QJsonObject wrapFileMessage(const Message::FileInfoStruct &fileMessageStruct);

private slots:
  void onTextMessageToSend(const QString &receiver, const QString &message);
};

#endif // MAINWINDOW_H
