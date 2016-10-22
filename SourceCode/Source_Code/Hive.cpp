#include "Hive.h"

Hive::Hive(QObject *parent) : QObject(parent)
{

#ifdef Q_OS_MAC
  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

  thread_data = new ThreadData(this);
  thread_net = new ThreadNet(this);
  gui_central_widget = new GuiCentralWidget();
  //QObject not compatible to QWidget, delete obj manually

  ////connect
  connect(thread_data, SIGNAL(refreshGuiInfo()), gui_central_widget, SLOT(refreshUI()), Qt::QueuedConnection);

  connect(thread_net, SIGNAL(usrEnter(UsrProfileStruct*)), thread_data, SLOT(onUsrEntered(UsrProfileStruct*)), Qt::AutoConnection);
  connect(thread_data, SIGNAL(usrProfileLoaded(UsrData*)), gui_central_widget, SLOT(addUsr(UsrData*)), Qt::QueuedConnection);
  connect(thread_data, SIGNAL(usrProfileChanged(UsrData*)), gui_central_widget, SLOT(changeUsr(UsrData*)), Qt::QueuedConnection);


  //bind to SIGNAL refreshGuiInfo();
//  connect(thread_data, SIGNAL(refreshChatStack(UserData*)), gui_central_widget->gui_main_block->gui_chat_stack, SLOT(setUserData(UserData*)));

  connect(gui_central_widget->gui_main_block->gui_chat_stack, SIGNAL(sendMessage(QString, QString)), this, SLOT(onTextMessageToSend(const QString &, const QString &)), Qt::QueuedConnection);
  connect(thread_net, SIGNAL(messageRecieved(Message::TextMessageStruct*, bool)), thread_data, SLOT(onMessageCome(Message::TextMessageStruct*, bool)), Qt::AutoConnection);
  connect(thread_data, SIGNAL(messageLoaded(Message::TextMessageStruct, bool)), gui_central_widget, SLOT(onMessageReceived(Message::TextMessageStruct, bool)), Qt::AutoConnection);


  thread_data->start(QThread::HighPriority);
  thread_net->start(QThread::HighPriority);

#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("Bye");
#endif

  gui_central_widget->close();
  gui_central_widget->deleteLater();

  thread_net->quit();
  thread_data->quit();
  if(!thread_net->wait(500))
    {
      thread_net->terminate();
      thread_net->wait();
    }
  if(!thread_data->wait(500))
    {
      thread_data->terminate();
      thread_data->wait();
    }
}


void Hive::onTextMessageToSend(const QString &receiver, const QString &message)
{
  QJsonObject json_object;
  json_object.insert("sender", GlobalData::g_settings_struct.profile_key_str);
  json_object.insert("receiver", receiver);
  json_object.insert("time", GlobalData::g_currentTime());
  json_object.insert("message", message);

  thread_net->udpSendMessage(json_object);
}

QJsonObject Hive::wrapTextMessage(const Message::TextMessageStruct &messageStruct)
{
  QJsonObject json_object;
  json_object.insert("sender", messageStruct.sender);
  json_object.insert("receiver", messageStruct.reciever);
  json_object.insert("time", messageStruct.time);
  json_object.insert("message", messageStruct.message);

  return json_object;
}

QJsonObject Hive::wrapFileMessage(const Message::FileInfoStruct &fileInfoStruct)
{
  QJsonObject json_object;
  json_object.insert("name", fileInfoStruct.name);
  json_object.insert("size", fileInfoStruct.size);
  json_object.insert("type", fileInfoStruct.type);

  return json_object;
}


