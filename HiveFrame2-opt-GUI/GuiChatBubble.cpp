#include "GuiChatBubble.h"

GuiChatBubble::GuiChatBubble(QString text, bool alignLeft = true, QWidget *parent) : QWidget(parent)
{
  strip_pixmap.load("/Users/Echo/Desktop/asp.png");
  strip_pixmap.setDevicePixelRatio(2.0);
  strip = new QLabel();
  strip->setPixmap(strip_pixmap);
  strip->setAlignment(Qt::AlignTop);
  strip->setContentsMargins(0,10,0,0);

  button = new GuiButton(text, 400,this);

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
  main_layout->addWidget(strip);
  main_layout->addWidget(button);


  this->setParent(parent);
  //this->setFixedHeight(button->height()+20);

}

