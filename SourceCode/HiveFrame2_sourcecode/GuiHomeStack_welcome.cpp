#include "GuiHomeStack_welcome.h"

GuiHomeStack_welcome::GuiHomeStack_welcome(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  ////profile widget
  profile_widget = new QWidget(this);

  my_avatar = new GuiAvatarButton(GlobalData::g_settings_struct.profile_avatar_str,175,this);
  my_avatar->setAlignment(Qt::AlignHCenter);

  welcome_label = new QLabel(this);
  welcome_label->setAlignment(Qt::AlignHCenter);
  welcome_label->setFont(GlobalData::font_chatBubble);

  ip_label = new QLabel(this);
  ip_label->setAlignment(Qt::AlignHCenter);
  ip_label->setFont(GlobalData::font_chatBubble);

  profile_layout = new QVBoxLayout(profile_widget);
  profile_layout->setAlignment(Qt::AlignCenter);
  profile_layout->addWidget(my_avatar);
  profile_layout->addWidget(welcome_label);
  profile_layout->addWidget(ip_label);

  ////!profile widget

  background_label = new QLabel(this);
  QPixmap background_pixmap(":/img/img/welcome_stack_background.png");
  background_pixmap.setDevicePixelRatio(2.0);
  background_label->setPixmap(background_pixmap);
  background_label->setAlignment(Qt::AlignRight|Qt::AlignBottom);


  QStackedLayout *dd = new QStackedLayout(this);
  dd->setAlignment(Qt::AlignCenter);
  dd->setStackingMode(QStackedLayout::StackAll);
  dd->addWidget(profile_widget);
  dd->addWidget(background_label);

  this->refreshUI();
}

void GuiHomeStack_welcome::refreshUI()
{
  int current_hour = QTime::currentTime().toString("hh").toInt();
  if(current_hour >= 4 && current_hour <= 12)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_settings_struct.profile_name_str).arg("Good Morning!"));
    }
  else if(current_hour >= 13 && current_hour <= 14)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_settings_struct.profile_name_str).arg("sleepy noon~"));
    }
  else if(current_hour >= 15 && current_hour <= 17)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_settings_struct.profile_name_str).arg("Good Afternoon!"));
    }
  else if(current_hour >= 18 && current_hour <= 23)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_settings_struct.profile_name_str).arg("Good Evening!"));
    }
  else if(current_hour >= 24 || current_hour <=3)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_settings_struct.profile_name_str).arg("It's late at night :)"));
    }

  my_avatar->setAvatar(GlobalData::g_settings_struct.profile_avatar_str);

  if(GlobalData::g_localHostIP.isEmpty())
    {
      ip_label->setText("<span style=\" color:#ed403f;\">●</span> You are Offline");
    }
  else
    {
      ip_label->setText(QString("<span style=\" color:#39c828;\">●</span> Your IP is: %1\n\n\n").arg(GlobalData::g_localHostIP));
    }
  qDebug()<<"#GuiWelcomeStack::refresh(): Finished";
}



