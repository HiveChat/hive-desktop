#include "Hive.h"

Hive::Hive(int &argc, char **argv)
  : QApplication(argc, argv)
{
  Global::window_dpr = this->devicePixelRatio();

#ifdef Q_OS_OSX
  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

  qDebug()<< "00:00:00 GUI_NORM  Hive::Hive() Main Thread Started: "<< this->thread()->currentThreadId();

  window = new Window();

  data_manager = new AppDataManager();
  data_manager->start();

  network_thread = new QThread(this);
  network_thread->start();

  network_manager = new NetworkManager();
  network_manager->moveToThread(network_thread);


  //! Qt SIGNAL SLOT connection between data_manager, network_manager, and window
  qRegisterMetaType<UsrProfile> ("UsrProfile");
  qRegisterMetaType<Message::TextMessage> ("Message::TextMessage");

  connect(data_manager, &AppDataManager::updatesAvailable,
          window, &Window::onUpdateAvailable,
          Qt::AutoConnection);
//  connect(network_manager->uv_server, &UvServer::usrEntered,
//          data_manager, &AppDataManager::onUsrEntered,
//          Qt::AutoConnection);
  connect(network_manager, &NetworkManager::updateAvailable,
          data_manager, &AppDataManager::onUpdatesAvailable,
          Qt::AutoConnection);
  connect(data_manager, &AppDataManager::usrProfileLoaded,
          window, &Window::addUsr,
          Qt::AutoConnection);
  connect(data_manager, &AppDataManager::usrProfileChanged,
          window, &Window::changeUsr,
          Qt::AutoConnection);
  connect(window->gui_main_block->gui_chat_stack, &ChatStack::sendMessage,
          this, &Hive::onTextMessageToSend,
          Qt::AutoConnection);
  connect(network_manager, &NetworkManager::messageRecieved,
          data_manager, &AppDataManager::onMessageCome,
          Qt::AutoConnection);
  connect(data_manager, &AppDataManager::messageLoaded,
          window, &Window::onMessageReceived,
          Qt::AutoConnection);

#ifdef Q_OS_OSX
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
  Log::gui(Log::Info, "Hive::~Hive()", "Destroying App");
#ifdef Q_OS_OSX
  QtMac::setBadgeLabelText("Bye");
#endif

  window->close();
  window->deleteLater();

  //! network_manager should be deleted to call destructor of NetworkManager,
  //! which closes uv loop in the child thread of NetworkManager
  network_manager->deleteLater();

  network_thread->quit();
//  data_manager->stop();
  data_manager->quit();


  if(!network_thread->wait(3000))
    {
      Log::gui(Log::Warning, "Hive::~Hive()", "Network thread is terminated due to timeout.");
      network_thread->terminate();
      network_thread->wait(3000);
    }

  if(!data_manager->wait(500))
    {
      Log::gui(Log::Warning, "Hive::~Hive()", "Data thread is terminated due to timeout.");
      data_manager->terminate();
      data_manager->wait(100);
    }

  data_manager->deleteLater();
  network_thread->deleteLater();

  Log::gui(Log::Info, "Hive::~Hive()", "Destroyed App");
}


void Hive::onTextMessageToSend(const QString &receiver, const QString &message)
{
  QJsonObject json_object;
  json_object.insert("sender", Global::settings.profile_key_str);
  json_object.insert("receiver", receiver);
  json_object.insert("time", Global::getCurrentTime());
  json_object.insert("message", message);

  network_manager->udpSendMessage(json_object);
}


bool Hive::event(QEvent* e)
{
    switch (e->type()) {
      case QEvent::ApplicationActivate:
        {
          window->showNormal();
          return true;
        }
#ifdef Q_OS_OSX
      case QEvent::FileOpen:
        {
          QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(e);
          qDebug() << "Open file" << openEvent->file();
          window->setWindowTitle(QString(openEvent->file()));
          return true;
        }
#endif
      default:
        {
          break;
        }
    }

    return QApplication::event(e);
}


//QJsonObject Hive::wrapTextMessage(const Message::TextMessage &messageStruct)
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


