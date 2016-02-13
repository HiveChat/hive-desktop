#include "GuiMainBlock.h"
#include <QPalette>
#include <QProgressBar>
#include <QFormLayout>
#include <QPainter>
#include <QGroupBox>


GuiMainBlock::GuiMainBlock(QWidget *parent) : QWidget(parent)
{
  text_palette.setColor(QPalette::WindowText, QColor(100,100,100));

  gui_welcome_stack = new GuiWelcomeStack(this);
  gui_settings_stack = new GuiScrollStack(this);

  main_stacked_widget = new QStackedWidget(this);
  main_stacked_widget->addWidget(gui_welcome_stack);
  main_stacked_widget->addWidget(gui_settings_stack);
  main_stacked_widget->setCurrentWidget(gui_settings_stack);
  //main_stacked_widget->setCurrentWidget(gui_welcome_stack);

  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(main_stacked_widget);

  setSettings_messaging();
}

GuiMainBlock::~GuiMainBlock()
{

}

/////////settings
void GuiMainBlock::setSettings_profile()
{
  gui_settings_stack->setIcon(":/img/img/profile_0.png");
  gui_settings_stack->setTitle("Settings");
  gui_settings_stack->setSubTitle("Profile");


}

void GuiMainBlock::setSettings_messaging()
{
  gui_settings_stack->setIcon(":/img/img/messaging.png");
  gui_settings_stack->setTitle("Settings");
  gui_settings_stack->setSubTitle("Messaging");

  QLabel *text_bubble_label = new QLabel("Text Bubble", this);
  QFont font("Futura");//Verdana
  text_bubble_label->setFont(font);
  text_bubble_label->setPalette(text_palette);

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(1);
  top_line->setFixedWidth(550);
  top_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: 0px transparent;  }");

  gui_settings_stack->central_layout->setAlignment(Qt::AlignCenter);
  gui_settings_stack->central_layout->addWidget(text_bubble_label);
  gui_settings_stack->central_layout->addWidget(top_line);
}

void GuiMainBlock::setHome_storage()
{
  gui_settings_stack->setIcon(":/img/img/storage.png");
  gui_settings_stack->setTitle("Home");
  gui_settings_stack->setSubTitle("Storage");


//  QProgressBar {
//      border: 1px solid #FFB500;
//      border-radius: 3px;
//      text-align: center;
//  }

//  QProgressBar::chunk {
//      background-color: #FFB500;

//  }

}



/////////!settings


void GuiMainBlock::displayChatStack(QString usrKey)
{
  main_stacked_widget->setCurrentWidget(gui_chat_stack_map.find(usrKey).value());
}

void GuiMainBlock::displayWelcomeStack()
{
  gui_welcome_stack->refreshTime();
  main_stacked_widget->setCurrentWidget(gui_welcome_stack);
}

void GuiMainBlock::addChatStack(QStringList usrInfoStrList)
{
  gui_chat_stack = new GuiChatStack(usrInfoStrList, this);
  main_stacked_widget->addWidget(gui_chat_stack);
  gui_chat_stack_map.insert(usrInfoStrList[0], gui_chat_stack);

  //connect(this, SIGNAL(whoseMessage(QStringList)), gui_chat_stack, SLOT(checkMessage(QStringList)));
}

void GuiMainBlock::onMessageRecieved(QStringList message_str_list, bool fromMe)
{
  //0to,1from
  if(fromMe)
    {
      gui_chat_stack_map.find(message_str_list[0]).value()->checkMessage(message_str_list, fromMe);
    }
  else
    {
      gui_chat_stack_map.find(message_str_list[1]).value()->checkMessage(message_str_list, fromMe);
    }
  //emit whoseMessage(message_str_list);
}





//QColor color = QColorDialog::getColor(Qt::white, this);

