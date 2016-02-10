#include "GuiSettingsStack.h"

/////////////main
GuiSettingsStack::GuiSettingsStack(QWidget *parent) : QWidget(parent)
{



  QPalette palette;
  palette.setColor(QPalette::Window, Qt::white);

  this->setAutoFillBackground(true);
  this->setPalette(palette);
  this->setParent(parent);
}

GuiSettingsStack::~GuiSettingsStack()
{

}

