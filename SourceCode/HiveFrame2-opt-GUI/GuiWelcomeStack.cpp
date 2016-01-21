#include "GuiWelcomeStack.h"

GuiWelcomeStack::GuiWelcomeStack(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  //255,204,0,255
  palette.setColor(QPalette::Window, QColor(255,255,255,0));
  this->setAutoFillBackground(true);
  this->setPalette(palette);

  icon_label = new GuiLabelButton(this);
  icon_label->setHoveredPixmap("/Users/Echo/Desktop/add.png");
  icon_label->setDefaultPixmap("/Users/Echo/Desktop/add.png");
  icon_label->setAlignment(Qt::AlignBottom);

  bottom_layout = new QHBoxLayout();
  bottom_layout->setStretch(0,0);
  bottom_layout->setAlignment(Qt::AlignBottom);
  bottom_layout->addWidget(icon_label);

  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignRight);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->addLayout(bottom_layout);


}

