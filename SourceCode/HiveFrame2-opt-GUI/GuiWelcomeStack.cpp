#include "GuiWelcomeStack.h"

GuiWelcomeStack::GuiWelcomeStack(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  ////profile widget
  profile_widget = new QWidget(this);

  QFont profile_font("Futura");

  my_avatar = new GuiAvatarButton("/Users/Echo/Desktop/AVATAR2.png",175,this);
  my_avatar->setAlignment(Qt::AlignHCenter);

  welcome_label = new QLabel(this);
  welcome_label->setAlignment(Qt::AlignHCenter);
  welcome_label->setFont(profile_font);

  ip_label = new QLabel(this);
  ip_label->setAlignment(Qt::AlignHCenter);
  ip_label->setFont(profile_font);

  profile_layout = new QVBoxLayout(profile_widget);
  profile_layout->setAlignment(Qt::AlignCenter);
  profile_layout->addWidget(my_avatar);
  profile_layout->addWidget(welcome_label);
  profile_layout->addWidget(ip_label);

  ////!profile widget

  background_label = new GuiLabelButton(this);
  background_label->setHoveredPixmap(":/img/img/welcome_stack_background.png");
  background_label->setDefaultPixmap(":/img/img/welcome_stack_background.png");
  background_label->setAlignment(Qt::AlignRight|Qt::AlignBottom);


  QStackedLayout *dd = new QStackedLayout(this);
  dd->setAlignment(Qt::AlignCenter);
  dd->setStackingMode(QStackedLayout::StackAll);
  dd->addWidget(profile_widget);
  dd->addWidget(background_label);


  this->refreshTime();
}

void GuiWelcomeStack::refreshTime()
{
  int current_hour = QTime::currentTime().toString("hh").toInt();
  if(current_hour >= 4 && current_hour <= 12)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_myNameStr).arg("Good Morning!"));
    }
  else if(current_hour >= 13 && current_hour <= 14)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_myNameStr).arg("sleepy noon~"));
    }
  else if(current_hour >= 15 && current_hour <= 17)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_myNameStr).arg("Good Afternoon!"));
    }
  else if(current_hour >= 18 && current_hour <= 23)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_myNameStr).arg("Good Evening!"));
    }
  else if(current_hour >= 24 || current_hour <=3)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_myNameStr).arg("It's late at night :)"));
    }
  ip_label->setText(QString("Your IP is: %1\n\n\n").arg(GlobalData::g_localHostIP));
}



