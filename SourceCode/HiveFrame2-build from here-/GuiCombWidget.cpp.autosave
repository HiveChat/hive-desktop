#include "GuiCombWidget.h"
#include <QDebug>


GuiCombWidget::GuiCombWidget(UsrProfileStruct *usrProfileStruct, QWidget *parent) : QWidget(parent)
{
  QPalette usr_name_palette;
  usr_name_palette.setColor(QPalette::WindowText, QColor(103,72,0));
  QFont usr_name_font("futura");//verdana
  usr_name_font.setPointSize(15);
  QFont ip_addr_font("futura");//Gill Sans
  ip_addr_font.setPointSize(11);

  ///usrKey<<usrName<<ipAddr<<avatarPathr
  avatar = new GuiAvatarButton(80,  this);
  usr_name_label = new QLabel(this);
  ip_addr_label = new QLabel(this);
  status_label = new QLabel(offline_str, this);

  usr_name_label->setPalette(usr_name_palette);
  usr_name_label->setFont(usr_name_font);

  ip_addr_label->setFont(ip_addr_font);

  net_status_layout = new QHBoxLayout();
  net_status_layout->setAlignment(Qt::AlignLeft);
  net_status_layout->addWidget(status_label);
  net_status_layout->addWidget(ip_addr_label);

  usr_info_layout = new QVBoxLayout();
  usr_info_layout->setSpacing(0);
  usr_info_layout->addWidget(usr_name_label);
  usr_info_layout->addLayout(net_status_layout);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->addWidget(avatar);
  main_layout->addLayout(usr_info_layout);

  hover_palette.setColor(QPalette::Window, default_window_color);

  setProfile(usrProfileStruct);

  this->setMinimumWidth(200);
  this->setPalette(hover_palette);
  this->setAutoFillBackground(true);
  this->setParent(parent);
}

GuiCombWidget::~GuiCombWidget()
{

}

UsrProfileStruct GuiCombWidget::usrProfile()
{
  return usr_profile;
}

void GuiCombWidget::setProfile(UsrProfileStruct *usrProfile)
{
  usr_profile = *usrProfile;
  avatar->setAvatar(usr_profile.avatar_str);
  usr_name_label->setText(usr_profile.name_str);
  ip_addr_label->setText(usr_profile.ip_str);

  if(usr_profile.ip_str == "" || usr_profile.ip_str == "Offline")
    {
      status_label->setText(offline_str);
    }
  else
    {
      status_label->setText(online_str);
    }

  return;
}


//////events

void GuiCombWidget::paintEvent(QPaintEvent *)
{
  QRectF rectangle(0, 0, this->width(), this->height());
  QPainter paint;
  paint.begin(this);
  paint.setPen(QPen(Qt::NoPen));
  paint.setBrush(QBrush(window_color,Qt::SolidPattern));

  paint.drawRoundedRect(rectangle,5,5);
  paint.end();
}

void GuiCombWidget::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked(usr_profile.key_str);
}

void GuiCombWidget::enterEvent(QEvent *)
{
  window_color = hovered_window_color;
  repaint();
  hovered = true;
}

void GuiCombWidget::leaveEvent(QEvent *)
{
  window_color = default_window_color;
  repaint();
  hovered = false;
}

//void GuiCombWidget::dragMoveEvent(QEvent *)
//{

//}


