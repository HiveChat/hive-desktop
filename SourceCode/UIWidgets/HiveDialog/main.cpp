#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget *w = new Widget("title","content");
  w->show();

  return a.exec();
}
