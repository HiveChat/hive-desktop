#include "AvatarComposer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AvatarComposer w(QSize(200,200));
  w.show();

  return a.exec();
}
