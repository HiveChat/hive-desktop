#include "Hive.h"

#include <QApplication>

void loadStyleSheet()
{
  QFile qss(":/qss/qss/comb_treewidget.qss");
  if(!qss.open(QFile::ReadOnly))
  {
      qDebug("can not open qss !");
      return;
  }
  qApp->setStyleSheet(qss.readAll());
}


int main(int argc, char *argv[])
{
  //! Register to Qt signal-slot meta type.
  qRegisterMetaType<UsrProfile> ("UsrProfile");
  qRegisterMetaType<Message::TextMessage> ("Message::TextMessage");

  Hive hiveApp(argc, argv);
  loadStyleSheet();
  hiveApp.window->show();

  return hiveApp.exec();
}
