#include "hiveswitch.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  HiveSwitch w;
  w.setWindowFlags(Qt::FramelessWindowHint);
  w.setAttribute(Qt::WA_TranslucentBackground);
  w.show();

  return a.exec();
}
