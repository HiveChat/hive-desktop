#include <QCoreApplication>
#include <NetManager.h>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  NetManager main_class;


  return a.exec();
}
