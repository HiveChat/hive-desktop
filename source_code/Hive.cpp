#include "Hive.h"

Hive::Hive(QObject *parent) : QObject(parent)
{

#ifdef Q_OS_OSX

  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

	qDebug()<<this->thread()->currentThreadId();
	thread_data = new ThreadData(this);
  thread_net = new ThreadNet(this);
  gui_central_widget = new GuiCentralWidget();
  //QObject not compatible to QWidget para, delete obj manually

  ////connect
	connect(thread_data, &ThreadData::updatesAvailable,
					gui_central_widget, &GuiCentralWidget::onUpdateAvailable,
          Qt::QueuedConnection);

	connect(thread_net, &ThreadNet::usrEnter,
          thread_data, &ThreadData::onUsrEntered,
          Qt::AutoConnection);
  connect(thread_net, &ThreadNet::updateAvailable,
          thread_data, &ThreadData::onUpdatesAvailable,
          Qt::AutoConnection);
  connect(thread_data, &ThreadData::usrProfileLoaded,
          gui_central_widget, &GuiCentralWidget::addUsr,
          Qt::QueuedConnection);
  connect(thread_data, &ThreadData::usrProfileChanged,
          gui_central_widget, &GuiCentralWidget::changeUsr,
          Qt::QueuedConnection);

  connect(gui_central_widget->gui_main_block->gui_chat_stack, &GuiChatStack::sendMessage,
          this, &Hive::onTextMessageToSend,
          Qt::QueuedConnection);
  connect(thread_net, &ThreadNet::messageRecieved,
          thread_data, &ThreadData::onMessageCome,
          Qt::AutoConnection);
  connect(thread_data, &ThreadData::messageLoaded,
          gui_central_widget, &GuiCentralWidget::onMessageReceived,
          Qt::AutoConnection);


	thread_data->start(QThread::NormalPriority);
	thread_net->start(QThread::NormalPriority);

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
  json_object.insert("sender", GlobalData::settings_struct.profile_key_str);
  json_object.insert("receiver", receiver);
  json_object.insert("time", GlobalData::getCurrentTime());
  json_object.insert("message", message);

  thread_net->udpSendMessage(json_object);
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
//  json_object.insert("type", fileInfoStruct.type);

//  return json_object;
//}


