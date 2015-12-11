#include "GuiButton.h"

GuiButton::GuiButton(QString text, int maxWidth, QWidget *parent)
{

  label = new QLabel();
  //label->setFixedWidth(maxWidth);
  label->setWordWrap(true);
  label->setText(text);
  //label->setAlignment(Qt::AlignTop);

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(10,10,10,10);
  main_layout->addWidget(label);

  this->setParent(parent);
  this->setFixedWidth(maxWidth);

  qDebug()<<label->width();
  qDebug()<<label->height();
}

void GuiButton::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(QColor(255,181,0),Qt::SolidPattern));
  painter.drawRoundedRect(0,0,label->rect().width()+20,label->rect().height()+20,10,10);
}

