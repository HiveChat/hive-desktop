#include "Hive.h"

#include <QApplication>
#ifndef Q_WS_QWS && Q_WS_QPA
#include <QPropertyAnimation>
#endif



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
  QString str = "Tim is stupid.";
  QByteArray sizeNum;
  sizeNum.append(str);

  QByteArray out_array;
  QDataStream out(&out_array, QIODevice::ReadWrite);
  out << sizeNum.size();


  qDebug()<<out;


  Hive hiveApp(argc, argv);
  loadMyStyle();
  hiveApp.gui_central_widget->show();

#ifndef Q_WS_QWS && Q_WS_QPA
  QPropertyAnimation animation(hiveApp.gui_central_widget, "geometry");
  animation.setDuration(300);
  animation.setStartValue(QRect(120, 80, GlobalData::settings_struct.window_width, GlobalData::settings_struct.window_height));
  animation.setEndValue(QRect(140, 100, GlobalData::settings_struct.window_width, GlobalData::settings_struct.window_height));
  animation.setEasingCurve(QEasingCurve::OutBounce);
  animation.start();
#endif

  return hiveApp.exec();
}
