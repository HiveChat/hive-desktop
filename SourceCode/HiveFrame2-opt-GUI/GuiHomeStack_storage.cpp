#include "GuiHomeStack_storage.h"

GuiHomeStack_storage::GuiHomeStack_storage(QWidget *parent)
{
  setIcon(":/img/img/storage.png");
  setTitle("Home");
  setSubTitle("storage");
  setTag("Overview");

  this->setParent(parent);
}

GuiHomeStack_storage::~GuiHomeStack_storage()
{

}

