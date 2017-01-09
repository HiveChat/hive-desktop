#include "Hive.h"
#include <QApplication>

#ifndef Q_OS_ANDROID
#ifndef Q_OS_IOS

#include <QPropertyAnimation>

#endif
#endif

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

#ifndef Q_OS_ANDROID
#ifndef Q_OS_IOS

//  if(!checkSingleInstance("topo-client.lock"))
//    {
//      return 1;
//    }

#endif
#endif


  QApplication a(argc, argv);

  loadMyStyle();

  Hive w;
  w.gui_central_widget->show();

#ifndef Q_OS_ANDROID
#ifndef Q_OS_IOS
  QPropertyAnimation animation(w.gui_central_widget, "geometry");
  animation.setDuration(300);
  animation.setStartValue(QRect(120, 80, 0, 0));
  animation.setEndValue(QRect(140, 100, 0, 0));
  animation.setEasingCurve(QEasingCurve::OutBounce);
  animation.start();
#endif
#endif

  return a.exec();
}
