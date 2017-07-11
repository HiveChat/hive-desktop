#include "_showcase.h"

_Showcase::_Showcase(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  QLabel *lb = new QLabel("hello", this);
  bt1 = new Button("hello", this);
  bt2 = new Button("hello dsa g fdsgd gregewr gr ewger g ew g reg rewg  g rewgerw gerg dagf dg fdsg", this);

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(lb);
  mainLayout->addWidget(bt1);
  mainLayout->addWidget(bt2);

}

_Showcase::~_Showcase()
{
  qDebug()<<"f";
  bt1->deleteLater();
  bt2->deleteLater();
  qDebug()<<"\f";

}
