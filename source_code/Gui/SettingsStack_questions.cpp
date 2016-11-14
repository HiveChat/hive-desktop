#include "SettingsStack_questions.h"


GuiSettingsStack_questions::GuiSettingsStack_questions(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  setIcon(":/img/img/question.png");
  setTitle("Settings");
  setSubTitle("questions");

  addTag("About Hive!");
  addItem("Copyright:", "©2015-2016 Tim Zheng (Ultrasilicon). All Rights Reserved.", false);
  addItem("Why Hive?", "Hive is designed for users without <b>Internet Access</b>. \nIt enables users to chat in <b>LAN</b> (Limited Area Network) connection.");

  addTag("Troubleshoot");
  addItem("Can't chat?", "<p><b>1.</b> Make sure that the person you are chatting to has installed the same version of Hive!</p>  <p><b>2.</b> You can only chat to the person who is in the same LAN</p>");
//  central_layout->addSpacing(20);
  addItem("IP indicator:", "<p><b><font color=#39c828>●</font>Online.</b></p>"
                           "<p><b><font color=#ed403f>●</font>Offline.</b> You are not connnected to any network, so Hive will not work.</p>"
                           "<p><b><font color=#ffb500>●</font>You are not in the same subnet with the person.</b> For example, if your IP is 192.168.1.101, you probably can't reach the person at 192.168.2.101. Change your network connection until your first three section of IP address is 192.168.2.*</p>");
  this->setParent(parent);
}

GuiSettingsStack_questions::~GuiSettingsStack_questions()
{

}

