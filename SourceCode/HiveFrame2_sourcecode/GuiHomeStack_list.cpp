#include "GuiHomeStack_list.h"
#include <QDebug>

GuiListItem::GuiListItem(UsrProfileStruct *usrProfileStruct, QWidget *parent) : QWidget(parent)
{
  avatar_button = new GuiAvatarButton(":/avatar/avatar/default.png", 90, this);
  name_label = new QLabel("Loading...", this);
  ip_label = new QLabel("Loading...", this);

  name_label->setFont(GlobalData::font_scrollStackSubtitle);
  ip_label->setFont(GlobalData::font_scrollStackSubtitle);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setSpacing(50);
  main_layout->addWidget(avatar_button);
  main_layout->addWidget(name_label);
  main_layout->addWidget(ip_label);

  refreshUsrProfile(usrProfileStruct);
}

GuiListItem::~GuiListItem()
{

}

void GuiListItem::refreshUsrProfile(UsrProfileStruct *usrProfileStruct)
{
  avatar_button->setAvatar(usrProfileStruct->avatar_str);
  name_label->setText(usrProfileStruct->name_str);
  ip_label->setText(usrProfileStruct->ip_str);
}


////////////////////////////////////////////////////////////////////////

GuiHomeStack_list::GuiHomeStack_list(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  this->setIcon(":/img/img/list.png");
  this->setTitle("Home");
  this->setSubTitle("online user");

  this->central_layout->setAlignment(Qt::AlignLeft);
  this->setParent(parent);
}

GuiHomeStack_list::~GuiHomeStack_list()
{

}

void GuiHomeStack_list::addUsr(UsrProfileStruct *usrProfileStruct)
{
  GuiListItem *list_item = new GuiListItem(usrProfileStruct, this);
  list_item_map.insert(usrProfileStruct->key_str, list_item);
  central_layout->addWidget(list_item);
}

void GuiHomeStack_list::refreshUsrProfile(UsrProfileStruct *usrProfileStruct)
{
  list_item_map.value(usrProfileStruct->key_str)->refreshUsrProfile(usrProfileStruct);
}





