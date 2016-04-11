#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GuiCentralWidget.h"
#include "GlobalData.h"

#include "ThreadData.h"
#include "ThreadInfo.h"
#include "ThreadNet.h"

#ifdef Q_OS_MAC
//#include <QtMacExtras>
#endif

class Hive : public QObject
{
  Q_OBJECT

public:
  Hive(QObject *parent = 0);
  ~Hive();

  GuiCentralWidget *gui_central_widget;
  ThreadData *thread_data;
  ThreadInfo *thread_info;
  ThreadNet *thread_net;

};

#endif // MAINWINDOW_H
