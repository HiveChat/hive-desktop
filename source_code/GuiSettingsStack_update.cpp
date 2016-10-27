#include "GuiSettingsStack_update.h"

GuiSettingsStack_update::GuiSettingsStack_update(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  setIcon(":/img/img/update.png");
  setTitle("Settings");
  setSubTitle("update");

  this->setParent(parent);
}
