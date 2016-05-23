#include "Hive.h"
#include "GuiOSXNotification.h"

Hive::Hive(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_MAC
  QApplication::setQuitOnLastWindowClosed(true);
  QtMac::setBadgeLabelText("Hi");
#endif

  ////data manager
  thread_data = new ThreadData(this);

  ////net manager
  thread_net = new ThreadNet(this);

  ////gui
  gui_central_widget = new GuiCentralWidget();

  ////connect
  connect(thread_data, SIGNAL(refreshGuiInfo()), gui_central_widget->gui_main_block->gui_home_stack_welcome, SLOT(refresh()), Qt::QueuedConnection);

  connect(thread_net, SIGNAL(usrEnter(UsrProfileStruct*)), thread_data, SLOT(onUsrEntered(UsrProfileStruct*)), Qt::AutoConnection);
  connect(thread_data, SIGNAL(usrProfileLoaded(UsrProfileStruct*)), gui_central_widget, SLOT(addUsr(UsrProfileStruct*)), Qt::QueuedConnection);
  connect(thread_data, SIGNAL(usrProfileChanged(UsrProfileStruct*)), gui_central_widget, SLOT(onUsrProfileChanged(UsrProfileStruct*)), Qt::QueuedConnection);

  connect(gui_central_widget->gui_main_block, SIGNAL(sendMessage(QString,QString)), thread_net, SLOT(sendMessage(QString,QString)), Qt::QueuedConnection);
  connect(thread_net, SIGNAL(messageRecieved(MessageStruct*,bool)), thread_data, SLOT(onMessageCome(MessageStruct*,bool)), Qt::AutoConnection);
  connect(thread_data, SIGNAL(messageLoaded(MessageStruct,bool)), gui_central_widget->gui_main_block, SLOT(onMessageRecieved(MessageStruct, bool)), Qt::AutoConnection);



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

  delete gui_central_widget;
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


