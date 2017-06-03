#include "hive.h"
#include <QLabel>
#include <QTextCodec>


int main(int argc, char *argv[])
{
  HiveApp hiveApp(argc, argv);

  uint a = 0x2FF4;

  QLabel *lab = new QLabel(QChar(a));
  lab->show();

  return hiveApp.exec();
}
