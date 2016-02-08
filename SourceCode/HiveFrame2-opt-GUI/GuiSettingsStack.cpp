#include "GuiSettingsStack.h"

//////////////////////////top//////////////////////////////////////
GuiSettingsStack_top_bar::GuiSettingsStack_top_bar(QWidget *parent) : QWidget(parent)
{
  ///usrKey<<usrName<<ipAddr<<avatarPathr
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  /*QPalette palette;
  palette.setColor(QPalette::Background, QColor(192,253,123));
  //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
  setPalette(palette);
///from baidu
*/

//  avatar_label = new GuiAvatarButton(usrInfoStrList[3], 90, this);
//  avatar_label->setFixedHeight(50);
//  avatar_label->setAlignment(Qt::AlignLeft);

//  //
//  QLabel *usr_name_label = new QLabel(usrInfoStrList[1]);
//  QLabel *usr_ip_label = new QLabel(usrInfoStrList[2]);

//  QFont usr_name_font("Futura");//Verdana
//  usr_name_font.setPointSize(15);
//  usr_name_label->setFont(usr_name_font);

//  QFont usr_ip_font("Futura");//Gill Sans
//  usr_ip_font.setPointSize(11);
//  usr_ip_label->setFont(usr_ip_font);

//  QVBoxLayout *usr_info_layout = new QVBoxLayout();
//  usr_info_layout->setContentsMargins(0,0,10,10);
//  usr_info_layout->addWidget(usr_name_label);
//  usr_info_layout->addWidget(usr_ip_label);


//  main_layout = new QHBoxLayout(this);
//  main_layout->setAlignment(Qt::AlignLeft);
//  main_layout->setContentsMargins(15,10,10,0);
//  main_layout->setSpacing(10);
//  main_layout->addWidget(avatar_label);
//  main_layout->addLayout(usr_info_layout);

  this->setFixedHeight(67);
}

GuiSettingsStack_top_bar::~GuiSettingsStack_top_bar()
{

}




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

