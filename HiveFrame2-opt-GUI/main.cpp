#include "mainwindow.h"
#include <QApplication>

int load_my_style()
{
  QFile  qss(":/qss/qss/comb_treewidget.qss");
  if(!qss.open(QFile::ReadOnly))
  {
      qDebug("can not open qss !");
      return 0;
  }
  qApp->setStyleSheet(qss.readAll());
  return (0);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  load_my_style();

  MainWindow w;
  w.show();

  return a.exec();
}
