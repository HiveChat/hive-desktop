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

  connect(gui_central_widget->gui_main_block->gui_chat_stack, SIGNAL(sendMessage(QString, QString)), thread_net, SLOT(udpSendMessage(QString, QString)), Qt::QueuedConnection);
  connect(thread_net, SIGNAL(messageRecieved(MessageStruct*, bool)), thread_data, SLOT(onMessageCome(MessageStruct*, bool)), Qt::AutoConnection);
  connect(thread_data, SIGNAL(messageLoaded(MessageStruct, bool)), gui_central_widget, SLOT(onMessageReceived(MessageStruct, bool)), Qt::AutoConnection);


  thread_data->start(QThread::NormalPriority);
  thread_net->start(QThread::NormalPriority);

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


