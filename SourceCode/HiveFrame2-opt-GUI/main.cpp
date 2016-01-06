#include "mainwindow.h"
#include <QApplication>
#include <QPropertyAnimation>


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

  QPropertyAnimation animation(&w, "geometry");
  animation.setDuration(300);
  animation.setStartValue(QRect(120, 80, 0, 0));
  animation.setEndValue(QRect(140, 100, 0, 0));
  animation.setEasingCurve(QEasingCurve::OutBounce);


  animation.start();
  w.show();



  return a.exec();
}
