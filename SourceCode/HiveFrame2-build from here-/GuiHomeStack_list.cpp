#include "GuiHomeStack_list.h"

GuiHomeStack_list::GuiHomeStack_list(QWidget *parent)
{
  setIcon(":/img/img/list.png");
  setTitle("Home");
  setSubTitle("online user");

  this->setParent(parent);
}

void GuiHomeStack_list::addUsr(UsrProfileStruct *usrProfileStruct)
{

  GuiAvatarButton *avatar_button = new GuiAvatarButton(usrProfileStruct->avatar_str, 50, this);
  QLabel *name_label = new QLabel(usrProfileStruct->name_str);
  QLabel *ip_label = new QLabel(usrProfileStruct->ip_str);

  QHBoxLayout *usr_item_layout = new QHBoxLayout();
  usr_item_layout->addWidget(avatar_button);
  usr_item_layout->addWidget(name_label);
  usr_item_layout->addWidget(ip_label);

  central_layout->addLayout(usr_item_layout);
}


