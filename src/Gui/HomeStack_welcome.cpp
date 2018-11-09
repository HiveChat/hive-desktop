#include "HomeStack_welcome.h"

HomeStack_welcome::HomeStack_welcome(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  ////profile widget
  profile_widget = new QWidget(this);

  my_avatar = new AvatarButton(Global::settings.profile_avatar_str,175,this);
  my_avatar->setAlignment(Qt::AlignHCenter);

  welcome_label = new QLabel(this);
  welcome_label->setAlignment(Qt::AlignHCenter);
  welcome_label->setFont(Global::font_chatBubble);

  ip_label = new QLabel(this);
  ip_label->setAlignment(Qt::AlignHCenter);
  ip_label->setFont(Global::font_chatBubble);

  profile_layout = new QVBoxLayout(profile_widget);
  profile_layout->setAlignment(Qt::AlignCenter);
  profile_layout->addWidget(my_avatar);
  profile_layout->addWidget(welcome_label);
  profile_layout->addWidget(ip_label);

  ////!profile widget

  background_label = new QLabel(this);
  QPixmap background_pixmap(":/img/img/welcome_stack_background.png");
  background_pixmap.setDevicePixelRatio(Global::window_dpr);
  background_label->setPixmap(background_pixmap);
  background_label->setAlignment(Qt::AlignRight|Qt::AlignBottom);


  QStackedLayout *dd = new QStackedLayout(this);
  dd->setAlignment(Qt::AlignCenter);
  dd->setStackingMode(QStackedLayout::StackAll);
  dd->addWidget(profile_widget);
  dd->addWidget(background_label);

  this->refreshUI();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout,
          this, &HomeStack_welcome::refreshUI);
  timer->setSingleShot(false);
  timer->start(1000);

}

void HomeStack_welcome::mouseReleaseEvent(QMouseEvent *)
{
//  if(ev->button() == Qt::LeftButton)
//    {
//      QVariantAnimation *file_tran_ani = new QVariantAnimation(this);
//      file_tran_ani->setStartValue(255);
//      file_tran_ani->setEndValue(0);
//      file_tran_ani->setDuration(3000);
//      file_tran_ani->setEasingCurve(QEasingCurve::OutCirc);
//      connect(file_tran_ani, &QVariantAnimation::valueChanged,
//              [this](QVariant value) {
//                QPalette palette;
//                palette.setColor(QPalette::Window, QColor(255,255,255,value.toInt()));
//                this->setPalette(palette);
//              });
//      file_tran_ani->start(QAbstractAnimation::DeleteWhenStopped);
//    }
}


void HomeStack_welcome::refreshUI()
{
  int current_hour = QTime::currentTime().toString("hh").toInt();
  if(current_hour >= 4 && current_hour <= 12)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(Global::settings.profile_name_str).arg("Good Morning!"));
    }
  else if(current_hour >= 13 && current_hour <= 14)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(Global::settings.profile_name_str).arg("sleepy noon~"));
    }
  else if(current_hour >= 15 && current_hour <= 17)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(Global::settings.profile_name_str).arg("Good Afternoon!"));
    }
  else if(current_hour >= 18 && current_hour <= 23)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(Global::settings.profile_name_str).arg("Good Evening!"));
    }
  else if(current_hour >= 24 || current_hour <=3)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(Global::settings.profile_name_str).arg("It's late at night :)"));
    }

  my_avatar->setAvatar(Global::settings.profile_avatar_str);

  UsrData *p = AppDataManager::usr_data_hash.value(Global::settings.profile_uuid_str);
  if(p && p->getUsrProfile())
    {
      if(!p->getUsrProfile()->online)
        {
          online = false;
          ip_label->setText("<span style=\" color:#ed403f;\">●</span> You are Offline");
        }
      else
        {
          online = true;
          ip_label->setText(QString("<span style=\" color:#39c828;\">●</span> Your IP is: %1\n\n\n").arg(p->getUsrProfile()->ip));
        }
    }
  Log::gui(Log::Info, "GuiWelcomeStack::refresh()", "Finished");

}



