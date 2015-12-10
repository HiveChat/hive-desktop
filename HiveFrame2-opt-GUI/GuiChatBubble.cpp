#include "GuiChatBubble.h"

GuiChatBubble::GuiChatBubble(QString text, bool alignLeft = true, QWidget *parent) : QWidget(parent)
{
  button = new GuiButton("hello", 100,this);

  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
  main_layout->addWidget(button);


  this->setParent(parent);
}

