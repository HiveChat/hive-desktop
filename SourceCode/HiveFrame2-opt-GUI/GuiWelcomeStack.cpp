#include "GuiWelcomeStack.h"

GuiWelcomeStack::GuiWelcomeStack(QWidget *parent) : QWidget(parent)
{
  ////profile widget
  profile_widget = new QWidget(this);

  QFont profile_font("Futura");

  my_avatar = new GuiAvatarButton("/Users/Echo/Desktop/AVATAR2.png",175,this);
  my_avatar->setAlignment(Qt::AlignHCenter);

  welcome_label = new QLabel(this);
  welcome_label->setAlignment(Qt::AlignHCenter);
  welcome_label->setFont(profile_font);
  ip_label = new QLabel("Your IP is: 192.168.1.1\n\n\n", this);
  ip_label->setAlignment(Qt::AlignHCenter);
  ip_label->setFont(profile_font);

  profile_layout = new QVBoxLayout(profile_widget);
  profile_layout->setAlignment(Qt::AlignCenter);
  profile_layout->addWidget(my_avatar);
  profile_layout->addWidget(welcome_label);
  profile_layout->addWidget(ip_label);

  ////!profile widget

  background_label = new GuiLabelButton(this);
  background_label->setHoveredPixmap("/Users/Echo/Desktop/add1.png");
  background_label->setDefaultPixmap("/Users/Echo/Desktop/add0.png");
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
  if(current_hour >= 4 && current_hour <= 11)
    {
      welcome_label->setText(QString("<b>%1</b>, %2").arg(GlobalData::g_myNameStr).arg("What A Nice Day!"));
    }
  else if(current_hour >= 12 && current_hour <= 14)
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
}



