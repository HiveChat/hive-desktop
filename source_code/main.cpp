#include "Hive.h"

#include <QApplication>
#include <QSharedMemory>
#ifndef Q_WS_QWS && Q_WS_QPA
#include <QPropertyAnimation>
#endif


bool checkSingleInstance(const char* program)
{
    static QSharedMemory shm(program);
    if(!shm.create(100))
    {
        return false;
    }
    return true;
}

int loadMyStyle()
{
  QFile qss(":/qss/qss/comb_treewidget.qss");
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

//#ifndef Q_WS_QWS && Q_WS_QPA
//  if(!checkSingleInstance("topo-client.lock"))
//    {
//      return 1;
//    }
//#endif


//  QApplication a(argc, argv);


  Hive hiveApp(argc, argv);
  loadMyStyle();
  hiveApp.gui_central_widget->show();

#ifndef Q_WS_QWS && Q_WS_QPA
  QPropertyAnimation animation(hiveApp.gui_central_widget, "geometry");
  animation.setDuration(300);
  animation.setStartValue(QRect(120, 80, 0, 0));
  animation.setEndValue(QRect(140, 100, 0, 0));
  animation.setEasingCurve(QEasingCurve::OutBounce);
  animation.start();
#endif

  return hiveApp.exec();
}
