#include "hive.h"
#include <QLabel>
#include <QTextCodec>

#include <ui/button.h>

int main(int argc, char *argv[])
{
  Hive hiveApp(argc, argv);
  hiveApp.central_widget->show();

  return hiveApp.exec();
}

