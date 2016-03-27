#include "mainwindow.h"
#include <QDebug>
#include <QPainter>

#ifdef Q_OS_MAC
#include <QtMacExtras>
#endif

#include "GuiOSXNotification.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("Hi");
#endif

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
  QApplication::setWindowIcon(QIcon(":/img/img/icon.png"));
  //this->setWindowFlags(Qt::FramelessWindowHint);
  //this->setWindowState(Qt::WindowNoState);

#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("");
#endif
}

MainWindow::~MainWindow()
{

}


