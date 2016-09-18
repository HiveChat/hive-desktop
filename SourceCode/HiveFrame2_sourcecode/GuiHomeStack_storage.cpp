#include "GuiHomeStack_storage.h"

GuiHomeStack_storage::GuiHomeStack_storage(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);
  this->setIcon(":/img/img/storage.png");
  this->setTitle("Home");
  this->setSubTitle("storage");
  this->addTag("Overview");

  this->setParent(parent);
}


