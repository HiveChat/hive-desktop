#include "GuiCombWidget.h"
#include <QDebug>


GuiCombWidget::GuiCombWidget(UsrProfileStruct *usrProfileStruct, QWidget *parent) : QWidget(parent)
{
  QPalette usr_name_palette;
  usr_name_palette.setColor(QPalette::WindowText, QColor(103,72,0));

  ///usrKey<<usrName<<ipAddr<<avatarPathr
  avatar = new GuiAvatarButton(80,  this);
  usr_name_label = new QLabel(this);
  ip_addr_label = new QLabel(this);
  status_label = new QLabel(offline_str, this);

  usr_name_label->setPalette(usr_name_palette);
  usr_name_label->setFont(GlobalData::font_combWidgetUsrName);

  ip_addr_label->setFont(GlobalData::font_combWidgetIpAddr);

  net_status_layout = new QHBoxLayout();
  net_status_layout->setAlignment(Qt::AlignLeft);
  net_status_layout->addWidget(status_label);
  net_status_layout->addWidget(ip_addr_label);

  usr_info_layout = new QVBoxLayout();
  usr_info_layout->setSpacing(0);
  usr_info_layout->addWidget(usr_name_label);
  usr_info_layout->addLayout(net_status_layout);

  badge_icon = new GuiBadgeIcon(14, this);
  badge_icon->setNumber(0);


  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->addSpacing(10);
//  main_layout->addWidget(badge_icon, Qt::AlignCenter);
  main_layout->addWidget(avatar);
  main_layout->addLayout(usr_info_layout);

  hover_palette.setColor(QPalette::Window, default_window_color);

  setProfile(usrProfileStruct);

  this->setMinimumWidth(200);
  this->setPalette(hover_palette);
  this->setAutoFillBackground(true);
  this->setToolTipDuration(1000);
}

GuiCombWidget::~GuiCombWidget()
{

}

void GuiCombWidget::setProfile(UsrProfileStruct *usrProfile)
{
  usr_profile = *usrProfile;

  avatar->setAvatar(usr_profile.avatar_str);
  usr_name_label->setText(usr_profile.name_str);
  ip_addr_label->setText(usr_profile.ip_str);

  if(usr_profile.ip_str.isEmpty() || usr_profile.ip_str == "Offline")
    {
      status_label->setText(offline_str);
      this->setToolTip("offline");
    }
  else
    {

      if(getSubNetStr(GlobalData::g_localHostIP) == getSubNetStr(usr_profile.ip_str))
        {
          status_label->setText(online_str);
          this->setToolTip("online");
        }
      else
        {
          status_label->setText(unstable_str);
          this->setToolTip("not in same subnet");
        }
    }

  return;
}

void GuiCombWidget::setBadgeNumber(const int &num)
{
  badge_icon->setNumber(num);
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

QString GuiCombWidget::getSubNetStr(QString &ipAddr)
{
  int loop_num = 0;
  QString sub_net_str;

  for(int i = 0; i < ipAddr.size(); i++)
    {
      if(ipAddr.at(i) == '.')
          loop_num ++;

      if(loop_num == 3)
          break;

      if(loop_num == 2)
          sub_net_str.append(ipAddr.at(i));
    }

  return sub_net_str;
}

//void GuiCombWidget::dragMoveEvent(QEvent *)
//{

//}


