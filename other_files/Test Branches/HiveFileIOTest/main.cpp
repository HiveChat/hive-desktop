#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QFile file("/Users/echo/Desktop/AP\ Statistcs.pdf");
  if(!file.open(QIODevice::ReadOnly))
    {
      return 1;
    }
  qDebug()<<"1";

  QFile dest("/Volumes/Data\ Lot/5122.base64");
  if(!dest.open(QIODevice::WriteOnly))
    {
      return 1;
    }

  while(!file.atEnd())
    {
      qDebug()<<dest.write(file.read(10000000).toBase64());
    }

  dest.flush();
  dest.close();

  file.flush();
  file.close();



  QFile input("/Volumes/Data\ Lot/5122.base64");
  if(!input.open(QIODevice::ReadOnly))
    {
      return 1;
    }

  QFile output("/Volumes/Data\ Lot/5123_rec.pdf");
  if(!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return 1;
    }
  while(!input.atEnd())
    {
      output.write(QByteArray::fromBase64(input.read(13333336)));
    }

  output.close();
  input.close();



  return a.exec();
}
