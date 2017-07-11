#include "_showcase.h"

_Showcase::_Showcase(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  bt1 = new Button("cancel", this);
  bt1->setPalette(Button::ForegroundHovered, QColor("#f7a527"));
  bt1->setPalette(Button::BackgroundHovered, QColor("#ffffff"));



  bt2 = new Button("invite", this);
  bt2->setPalette(Button::ForegroundDefault, QColor("#f7a527"));
  bt2->setPalette(Button::ForegroundHovered, QColor("#f7a527"));
  bt2->setPalette(Button::BackgroundHovered, QColor("#f9f2d2"));




  QHBoxLayout *mainLayout = new QHBoxLayout(this);
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
