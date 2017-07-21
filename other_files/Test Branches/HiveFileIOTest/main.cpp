#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QFile file("/Users/echo/Downloads/pipesocks-2.3-macOS.dmg");
  if(!file.open(QIODevice::ReadOnly))
    {
      return 1;
    }

  QFile dest("/Volumes/VirtualDisk/out.str");
  if(!dest.open(QIODevice::WriteOnly))
    {
      return 1;
    }

  while(!file.atEnd())
    {
      qDebug()<<"loop";
      std::string str = file.read(10000000).toStdString();
      qDebug()<<dest.write(str.c_str(), str.size());
//      qDebug()<<str;
    }

  dest.flush();
  dest.close();

  file.flush();
  file.close();



  QFile input("/Volumes/VirtualDisk/out.str");
  if(!input.open(QIODevice::ReadOnly))
    {
      return 1;
    }

  QFile output("/Volumes/VirtualDisk/out.dmg");
  if(!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return 1;
    }
  while(!input.atEnd())
    {
      output.write(QByteArray(input.read(13333336)));
    }

  output.flush();
  output.close();

  input.flush();
  input.close();



  return a.exec();
}
