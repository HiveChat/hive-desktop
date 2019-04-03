#include "Hive.h"
#include <QApplication>

#ifdef Q_OS_OSX
namespace Cocoa
{
  void changeTitleBarColor(WId winId, double red, double green, double blue, double alpha);
}
#endif

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
//  loadStyleSheet();
  hiveApp.window->show();

#ifdef Q_OS_OSX
  Cocoa::changeTitleBarColor(hiveApp.window->effectiveWinId(), 255./255., 255./255., 255./255., .95);
#endif

  return hiveApp.exec();
}
