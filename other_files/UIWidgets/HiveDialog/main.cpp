#include "HiveDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  HiveDialog *w = new HiveDialog("title","content");
  w->show();

  return a.exec();
}
