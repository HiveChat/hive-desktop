#include "GuiSettingsStack_questions.h"


GuiSettingsStack_questions::GuiSettingsStack_questions(QWidget *parent)
{
  setIcon(":/img/img/question.png");
  setTitle("Settings");
  setSubTitle("questions");
  setTag("About Hive!");

//  QFormLayout *formLayout = new QFormLayout;
//  formLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);
//  formLayout->addRow("Author:", new QLabel("Tim Zheng", this));
//  formLayout->addRow("Why Hive?", new QLabel("Hive is designed for users who don't get Internet access. It enables users to chat in LAN (Limited Area Network) connection. For example, you can chat with your friend with the connection to the same WiFi router which guarantees that you are in the same LAN network and you can send data to each other. Accroding to the principle it works, the router hive is working with doesn't necessarily need to connect the Internet Cable.", this));
//  central_layout->addLayout(formLayout);

  addItem("Author:", "Tim Zheng");
  addItem("Why Hive?", "Hive is designed for users who don't get Internet access. It enables users to chat in LAN (Limited Area Network) connection. For example, you can chat with your friend with the connection to the same WiFi router which guarantees that you are in the same LAN network and you can send data to each other. Accroding to the principle it works, the router hive is working with doesn't necessarily need to connect the Internet Cable.");

  this->setParent(parent);
}

GuiSettingsStack_questions::~GuiSettingsStack_questions()
{

}

