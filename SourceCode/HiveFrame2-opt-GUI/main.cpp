#include "mainwindow.h"
#include <QApplication>
#include <QPropertyAnimation>
#include <QSharedMemory>

bool checkSingleInstance(const char* program)
{
    static QSharedMemory shm(program);
    if(!shm.create(100))
    {
        return false;
    }
    return true;
}

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

  ///Check single instance.
  if(!checkSingleInstance("topo-client.lock"))
    {
      //return 1;
    }

  ///Construction
  QApplication a(argc, argv);

  load_my_style();

  MainWindow w;

  QPropertyAnimation animation(&w, "geometry");
  animation.setDuration(300);
  animation.setStartValue(QRect(120, 80, 0, 0));
  animation.setEndValue(QRect(140, 100, 0, 0));
  animation.setEasingCurve(QEasingCurve::OutBounce);
  animation.start();

  w.show();

  return a.exec();
}
