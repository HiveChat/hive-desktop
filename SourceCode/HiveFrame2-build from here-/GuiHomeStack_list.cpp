#include "GuiHomeStack_list.h"
#include <QDebug>

GuiListItem::GuiListItem(UsrProfileStruct *usrProfileStruct, QWidget *parent)
{
  avatar_button = new GuiAvatarButton(usrProfileStruct->avatar_str, 50, this);
  name_label = new QLabel(usrProfileStruct->name_str, this);
  ip_label = new QLabel(usrProfileStruct->ip_str, this);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setSpacing(50);
  main_layout->addWidget(avatar_button);
  main_layout->addWidget(name_label);
  main_layout->addWidget(ip_label);

  ///下面是第一次调用不会崩溃？

  this->setParent(parent);
}

GuiListItem::~GuiListItem()
{

}

void GuiListItem::refreshUsrProfile(UsrProfileStruct *usrProfileStruct)
{
  qDebug()<<"准备崩溃！3，2，1";
  a++;
//  avatar_button->setDisabled(true);
}




GuiHomeStack_list::GuiHomeStack_list(QWidget *parent)
{
  setIcon(":/img/img/list.png");
  setTitle("Home");
  setSubTitle("online user");

  this->setParent(parent);
}

GuiHomeStack_list::~GuiHomeStack_list()
{

}

void GuiHomeStack_list::addUsr(UsrProfileStruct *usrProfileStruct)
{
  GuiListItem *list_item = new GuiListItem(usrProfileStruct, this);
//  list_item_map.insert(usrProfileStruct->key_str, list_item);
  central_layout->addWidget(list_item);
}

void GuiHomeStack_list::refreshUsrProfile(UsrProfileStruct *usrProfileStruct)
{
  qDebug()<<list_item_map.value(usrProfileStruct->key_str)->objectName();//->refreshUsrProfile(usrProfileStruct);
}





