#include "mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <GuiOSXNotification.h>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  //QtMac::setBadgeLabelText("贺");

  QPalette palette;
  palette.setColor(QPalette::Window, QColor(250,250,250));
  this->setPalette(palette);

  gui_central_widget = new GuiCentralWidget(this);

  this->setMinimumHeight(600);
  this->setMinimumWidth(900);
  this->setCentralWidget(gui_central_widget);
  this->setWindowTitle("Hive!");
  this->setAttribute(Qt::WA_TranslucentBackground);

  QApplication::setQuitOnLastWindowClosed(false);
  //this->setWindowFlags(Qt::FramelessWindowHint);
  //this->setWindowState(Qt::WindowNoState);

}

MainWindow::~MainWindow()
{

}


