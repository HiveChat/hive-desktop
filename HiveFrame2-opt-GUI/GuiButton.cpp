#include "GuiButton.h"

GuiButton::GuiButton(QString text, int maxWidth, QWidget *parent)
{

  QFont font("Verdana");
  font.setPixelSize(14);

  label = new QLabel();
  label->setWordWrap(true);
  label->setText(text);
  label->setFont(font);

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(15,15,15,15);
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
  painter.drawRoundedRect(0,0,label->rect().width()+30,label->rect().height()+30,10,10);
}

