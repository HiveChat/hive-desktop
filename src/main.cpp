#include "Hive.h"

#include <QApplication>
//#include "Gui/macos/WindowOptions.h"

namespace Cocoa
{
  void changeTitleBarColor(WId winId, double red, double green, double blue, double alpha);
}


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

  Cocoa::changeTitleBarColor(hiveApp.window->effectiveWinId(), 255./255., 255./255., 255./255., .95);


  return hiveApp.exec();
}
