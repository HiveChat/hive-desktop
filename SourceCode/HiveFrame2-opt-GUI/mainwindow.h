#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GuiCentralWidget.h"
#include "GlobalData.h"

#include <QMainWindow>
#include <QtMac>
#include <qmacfunctions.h>
#include <QApplication>
#include <QPainter>

//#include "frameless_helper.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();


  int countFlag(QPoint p, int row);
  void setCursorType(int flag);
  int countRow(QPoint p);

protected:
  void paintEvent(QPaintEvent*);

//  QPoint move_point;

//  bool mouse_pressed;
//  void mousePressEvent(QMouseEvent *event);
//  void mouseReleaseEvent(QMouseEvent *event);
//  void mouseMoveEvent(QMouseEvent *event);

private:

  bool maximized = false;
  GuiCentralWidget *gui_central_widget;

private slots:
  void setWindowMaximized();

};

#endif // MAINWINDOW_H
