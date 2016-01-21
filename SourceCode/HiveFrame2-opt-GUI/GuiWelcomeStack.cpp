#include "GuiWelcomeStack.h"

GuiWelcomeStack::GuiWelcomeStack(QWidget *parent) : QWidget(parent)
{

  profile_widget = new QWidget(this);

  my_avatar = new GuiAvatarButton("/Users/Echo/Desktop/AVATAR2.png",175,this);

  usr_name_label = new QLabel("User Name", this);
  welcome_label = new QLabel("Good Morning", this);
  ip_label = new QLabel("IP Address", this);
  host_name_label = new QLabel("Host Name", this);

  profile_layout = new QVBoxLayout(profile_widget);
  profile_layout->setAlignment(Qt::AlignCenter);
  profile_layout->addWidget(my_avatar);
  profile_layout->addWidget(usr_name_label);
  profile_layout->addWidget(welcome_label);
  profile_layout->addWidget(ip_label);
  profile_layout->addWidget(host_name_label);







  background_label = new GuiLabelButton(this);
  background_label->setHoveredPixmap("/Users/Echo/Desktop/add1.png");
  background_label->setDefaultPixmap("/Users/Echo/Desktop/add0.png");
  background_label->setAlignment(Qt::AlignRight|Qt::AlignBottom);

//  bottom_layout = new QHBoxLayout(this);
//  bottom_layout->setContentsMargins(0,0,0,0);
//  bottom_layout->setAlignment(Qt::AlignBottom);
//  bottom_layout->addWidget(background_label);

  QStackedLayout *dd = new QStackedLayout(this);
  dd->setAlignment(Qt::AlignCenter);
  dd->setStackingMode(QStackedLayout::StackAll);
  dd->addWidget(background_label);
  dd->addWidget(profile_widget);




}

