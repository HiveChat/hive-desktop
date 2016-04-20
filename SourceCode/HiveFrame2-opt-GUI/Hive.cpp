#include <QApplication>

#ifdef Q_OS_MAC
#include <QtMac>
#endif

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
  connect(thread_net, SIGNAL(usrEnter(UsrProfileStruct*)), thread_data, SLOT(onUsrEnter(UsrProfileStruct*)));
  connect(thread_data, SIGNAL(usrProfileLoaded(UsrProfileStruct*)), gui_central_widget, SLOT(onUsrEnter(UsrProfileStruct*)));

  thread_net->start(QThread::NormalPriority);
#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
  delete gui_central_widget;
}


