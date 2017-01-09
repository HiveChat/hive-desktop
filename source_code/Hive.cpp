#include "Hive.h"

Hive::Hive(QObject *parent) : QObject(parent)
{

#ifdef Q_OS_OSX

  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

  qDebug()<<this->thread()->currentThreadId();

  data_thread = new QThread(this);
  data_thread->start();

  data_manager = new DataManager();
  data_manager->moveToThread(data_thread);

  network_thread = new QThread(this);
  network_thread->start();

  network_manager = new NetworkManager();
  network_manager->moveToThread(network_thread);

  gui_central_widget = new GuiCentralWidget();
  //QObject not compatible to QWidget para, delete obj manually


  ////connect
  qRegisterMetaType<UsrProfileStruct> ("UsrProfileStruct");
  qRegisterMetaType<Message::TextMessageStruct> ("Message::TextMessageStruct");

  connect(data_manager, &DataManager::updatesAvailable,
          gui_central_widget, &GuiCentralWidget::onUpdateAvailable,
          Qt::AutoConnection);

  connect(network_manager, &NetworkManager::usrEnter,
          data_manager, &DataManager::onUsrEntered,
          Qt::AutoConnection);
  connect(network_manager, &NetworkManager::updateAvailable,
          data_manager, &DataManager::onUpdatesAvailable,
          Qt::AutoConnection);
  connect(data_manager, &DataManager::usrProfileLoaded,
          gui_central_widget, &GuiCentralWidget::addUsr,
          Qt::AutoConnection);
  connect(data_manager, &DataManager::usrProfileChanged,
          gui_central_widget, &GuiCentralWidget::changeUsr,
          Qt::AutoConnection);

  connect(gui_central_widget->gui_main_block->gui_chat_stack, &GuiChatStack::sendMessage,
          this, &Hive::onTextMessageToSend,
          Qt::AutoConnection);
  connect(network_manager, &NetworkManager::messageRecieved,
          data_manager, &DataManager::onMessageCome,
          Qt::AutoConnection);
  connect(data_manager, &DataManager::messageLoaded,
          gui_central_widget, &GuiCentralWidget::onMessageReceived,
          Qt::AutoConnection);

#ifdef Q_OS_OSX
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
#ifdef Q_OS_OSX

  QtMac::setBadgeLabelText("Bye");
#endif

  gui_central_widget->close();
  gui_central_widget->deleteLater();

//  network_manager->deleteLater();
//  data_manager->deleteLater();

  network_thread->quit();
  data_thread->quit();

  if(!network_thread->wait(500))
    {
      network_thread->terminate();
      network_thread->wait();
    }
  if(!data_thread->wait(500))
    {
      data_thread->terminate();
      data_thread->wait();
    }
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


