#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w(QSize(200,200));
  w.show();

  return a.exec();
}
