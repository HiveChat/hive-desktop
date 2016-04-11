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

  gui_central_widget = new GuiCentralWidget();
  QApplication::setWindowIcon(QIcon(":/img/img/icon.png"));

#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
  delete gui_central_widget;
}


