#include "Hive.h"

Hive::Hive(int &argc, char **argv) : QApplication(argc, argv)

{
#ifdef Q_OS_OSX

  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

  qDebug()<< "xx:xx:xx GUI_NORM  Hive::Hive() Main Thread Started: "<< this->thread()->currentThreadId();

  data_thread = new QThread(this);
  data_thread->start();

  data_manager = new AppDataManager();
  data_manager->moveToThread(data_thread);

  network_thread = new QThread(this);
  network_thread->start();

  network_manager = new NetworkManager();
  network_manager->moveToThread(network_thread);

  //QObject not compatible to QWidget para, delete obj manually
  gui_central_widget = new CentralWidget();

  ////connect
  qRegisterMetaType<UsrProfileStruct> ("UsrProfileStruct");
  qRegisterMetaType<Message::TextMessageStruct> ("Message::TextMessageStruct");

  connect(data_manager, &AppDataManager::updatesAvailable,
          gui_central_widget, &CentralWidget::onUpdateAvailable,
          Qt::AutoConnection);

  connect(network_manager, &NetworkManager::usrEnter,
          data_manager, &AppDataManager::onUsrEntered,
          Qt::AutoConnection);
  connect(network_manager, &NetworkManager::updateAvailable,
          data_manager, &AppDataManager::onUpdatesAvailable,
          Qt::AutoConnection);
  connect(data_manager, &AppDataManager::usrProfileLoaded,
          gui_central_widget, &CentralWidget::addUsr,
          Qt::AutoConnection);
  connect(data_manager, &AppDataManager::usrProfileChanged,
          gui_central_widget, &CentralWidget::changeUsr,
          Qt::AutoConnection);

  connect(gui_central_widget->gui_main_block->gui_chat_stack, &GuiChatStack::sendMessage,
          this, &Hive::onTextMessageToSend,
          Qt::AutoConnection);
  connect(network_manager, &NetworkManager::messageRecieved,
          data_manager, &AppDataManager::onMessageCome,
          Qt::AutoConnection);
  connect(data_manager, &AppDataManager::messageLoaded,
          gui_central_widget, &CentralWidget::onMessageReceived,
          Qt::AutoConnection);

#ifdef Q_OS_OSX
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
  Log::gui(Log::Normal, "Hive::~Hive()", "Destroying App");
#ifdef Q_OS_OSX

  QtMac::setBadgeLabelText("Bye");
#endif

  gui_central_widget->close();
  gui_central_widget->deleteLater();


  network_thread->quit();
  data_thread->quit();

  if(!network_thread->wait(500))
    {
      Log::gui(Log::Error, "Hive::~Hive()", "Network thread is terminated due to timeout.");
      network_thread->terminate();
      network_thread->wait();
    }
  if(!data_thread->wait(500))
    {
      Log::gui(Log::Error, "Hive::~Hive()", "Data thread is terminated due to timeout.");
      data_thread->terminate();
      data_thread->wait();
    }

  network_manager->deleteLater();
  data_manager->deleteLater();

  Log::gui(Log::Normal, "Hive::~Hive()", "Destroyed App");

}


void Hive::onTextMessageToSend(const QString &receiver, const QString &message)
{
  QJsonObject json_object;
  json_object.insert("sender", GlobalData::settings_struct.profile_key_str);
  json_object.insert("receiver", receiver);
  json_object.insert("time", GlobalData::getCurrentTime());
  json_object.insert("message", message);

  network_manager->udpSendMessage(json_object);
}

bool Hive::event(QEvent* event)
{
    switch (event->type()) {
      case QEvent::ApplicationActivate:
        {
          gui_central_widget->showNormal();
          return true;
        }
#ifdef Q_OS_OSX
      case QEvent::FileOpen:
        {
          QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
          qDebug() << "Open file" << openEvent->file();
          gui_central_widget->setWindowTitle(QString(openEvent->file()));
          return true;
        }
#endif
      default:
        {
          break;
        }
    }

    return QApplication::event(event);
}


//QJsonObject Hive::wrapTextMessage(const Message::TextMessageStruct &messageStruct)
//{
//  QJsonObject json_object;
//  json_object.insert("sender", messageStruct.sender);
//  json_object.insert("receiver", messageStruct.reciever);
//  json_object.insert("time", messageStruct.time);
//  json_object.insert("message", messageStruct.message);
//  return json_object;
//}

//QJsonObject Hive::wrapFileMessage(const Message::FileInfoStruct &fileInfoStruct)
//{
//  QJsonObject json_object;
//  json_object.insert("name", fileInfoStruct.name);
//  json_object.insert("size", fileInfoStruct.size);
//  json_object.insert("type", fileInfoStruct.type);p
//  return json_object;
//}


