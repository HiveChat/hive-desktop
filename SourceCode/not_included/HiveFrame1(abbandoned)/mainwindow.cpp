#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  setWindowTitle("Hive!");
  CentralWidget *centralWidget = new CentralWidget(this);
  this->setCentralWidget(centralWidget);
  centralWidget->message_browser->setText("sffdfdfafds");

}

MainWindow::~MainWindow()
{
  deleteLater();
}
