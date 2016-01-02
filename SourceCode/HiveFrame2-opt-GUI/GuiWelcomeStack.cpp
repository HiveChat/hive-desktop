#include "GuiWelcomeStack.h"

GuiWelcomeStack::GuiWelcomeStack(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  //255,204,0,255
  palette.setColor(QPalette::Window, QColor(255,255,255,0));
  this->setAutoFillBackground(true);
  this->setPalette(palette);

  icon_pixmap.load(":/img/img/icon.png");
  icon_pixmap.setDevicePixelRatio(2.0);

  icon_label = new QLabel();
  icon_label->setPixmap(icon_pixmap);
  icon_label->setAlignment(Qt::AlignCenter);

  main_layout = new QVBoxLayout(this);
  main_layout->addWidget(icon_label);

}

