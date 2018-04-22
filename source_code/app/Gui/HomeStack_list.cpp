#include "HomeStack_list.h"
#include <QDebug>

ListItem::ListItem(UsrProfile *usrProfileStruct, QWidget *parent) : QWidget(parent)
{
  avatar_button = new AvatarButton(":/avatar/avatar/default.png", 90, this);
  name_label = new QLabel("Loading...", this);
  ip_label = new QLabel("Loading...", this);

  name_label->setFont(Global::font_scrollStackSubtitle);
  ip_label->setFont(Global::font_scrollStackSubtitle);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setSpacing(50);
  main_layout->addWidget(avatar_button);
  main_layout->addWidget(name_label);
  main_layout->addWidget(ip_label);

  refreshUsrProfile(usrProfileStruct);
}

ListItem::~ListItem()
{

}

void ListItem::refreshUsrProfile(UsrProfile *usrProfileStruct)
{
  avatar_button->setAvatar(usrProfileStruct->avatar);
  name_label->setText(usrProfileStruct->name);
  ip_label->setText(usrProfileStruct->ip);
}


////////////////////////////////////////////////////////////////////////

HomeStack_list::HomeStack_list(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  this->setIcon(":/img/img/list.png");
  this->setTitle("Home");
  this->setSubTitle("online user");

  this->central_layout->setAlignment(Qt::AlignLeft);
  this->setParent(parent);
}

HomeStack_list::~HomeStack_list()
{

}

void HomeStack_list::addUsr(UsrProfile *usrProfileStruct)
{
  ListItem *list_item = new ListItem(usrProfileStruct, this);
  list_item_hash.insert(usrProfileStruct->key, list_item);
  central_layout->addWidget(list_item);
}

void HomeStack_list::refreshUsrProfile(UsrProfile *usrProfileStruct)
{
  list_item_hash.value(usrProfileStruct->key)->refreshUsrProfile(usrProfileStruct);
}





