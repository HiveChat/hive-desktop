#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GuiCentralWidget.h"

#include <QMainWindow>
#include <QApplication>
#include <QPainter>


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

  QPoint move_point; //移动的距离

  bool mouse_pressed; //鼠标按下
  //鼠标按下事件
  void mousePressEvent(QMouseEvent *event);
 //鼠标释放事件
  void mouseReleaseEvent(QMouseEvent *event);
 //鼠标移动事件
  void mouseMoveEvent(QMouseEvent *event);

private:

  bool maximized = false;
  GuiCentralWidget *gui_central_widget;

private slots:
  void setWindowMaximized();

};

#endif // MAINWINDOW_H
