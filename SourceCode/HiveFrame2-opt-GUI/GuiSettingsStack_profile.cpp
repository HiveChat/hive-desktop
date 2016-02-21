#include "GuiSettingsStack_profile.h"

GuiSettingsStack_profile::GuiSettingsStack_profile(QWidget *parent)
{
  setIcon(":/img/img/profile_0.png");
  setTitle("Settings");
  setSubTitle("profile");

  QLabel *usr_info_label = new QLabel("User information", this);
  QFont font("Futura");//Verdana
  font.setPointSize(15);
  usr_info_label->setFont(font);
  usr_info_label->setPalette(text_palette);

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(1);
  top_line->setFixedWidth(580);
  top_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: 0px transparent;  }");


  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->addWidget(usr_info_label);
  central_layout->addWidget(top_line);
//  central_layout->addSpacing(15);

  this->setParent(parent);
}

GuiSettingsStack_profile::~GuiSettingsStack_profile()
{

}

