#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GuiCentralWidget.h"
#include "GlobalData.h"

#include <QMainWindow>
#include <QtMac>
#include <qmacfunctions.h>
#include <QApplication>
#include <QPainter>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();


private:
  GuiCentralWidget *gui_central_widget;


};

#endif // MAINWINDOW_H
