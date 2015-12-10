#include "GuiButton.h"

GuiButton::GuiButton(QString text, int maximumWidth, QWidget *parent)
{
  label = new QLabel("text");
  label->setWordWrap(true);
  label->setMaximumWidth(maximumWidth);
  width = label->width()+10;
  height = label->height()+10;

  rect.setX(0);
  rect.setY(0);
  rect.setWidth(100);
  rect.setHeight(70);

  main_layout = new QHBoxLayout(this);
  main_layout->addWidget(label);
  
  this->setParent(parent);
}

void GuiButton::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(QColor(255,181,0),Qt::SolidPattern));
  painter.drawRect(0,0,100,100);
}

