#include "Hive.h"

#include <QApplication>



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
  Hive hiveApp(argc, argv);
  loadMyStyle();
  hiveApp.gui_central_widget->show();

  return hiveApp.exec();
}
