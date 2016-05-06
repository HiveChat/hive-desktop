#include "Hive.h"
#include "GuiOSXNotification.h"

Hive::Hive(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_MAC
  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

  ////data manager
  thread_data = new ThreadData(this);

  ////net manager
  thread_net = new ThreadNet(this);

  ////gui
  gui_central_widget = new GuiCentralWidget();

  ////connect
  connect(thread_net, SIGNAL(usrEnter(UsrProfileStruct*)), thread_data, SLOT(onUsrEntered(UsrProfileStruct*)));
  connect(thread_data, SIGNAL(usrProfileLoaded(UsrProfileStruct*)), gui_central_widget, SLOT(onUsrEnter(UsrProfileStruct*)));
  connect(thread_data, SIGNAL(usrProfileChanged(UsrProfileStruct*)), gui_central_widget, SLOT(onUsrProfileChanged(UsrProfileStruct*)));
  connect(thread_net, SIGNAL(messageRecieved(MessageStruct*,bool)), thread_data, SLOT(onMessageCome(MessageStruct*,bool)));
  connect(thread_data, SIGNAL(messageLoaded(MessageStruct,bool)), gui_central_widget->gui_main_block, SLOT(onMessageRecieved(MessageStruct, bool)));

  connect(thread_data, SIGNAL(refreshWelcomeStack()), gui_central_widget->gui_main_block->gui_welcome_stack, SLOT(refresh()));

  connect(gui_central_widget->gui_main_block, SIGNAL(sendMessage(QString,QString)), thread_net, SLOT(sendMessage(QString,QString)));

  thread_data->start(QThread::NormalPriority);
  thread_net->start(QThread::NormalPriority);


#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
  delete gui_central_widget;
}


