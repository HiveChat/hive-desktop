#include "GuiMainBlock.h"
#include <QPalette>
#include <QProgressBar>
#include <QFormLayout>
#include <QPainter>
#include <QGroupBox>


GuiMainBlock::GuiMainBlock(QWidget *parent) : QWidget(parent)
{
  gui_welcome_stack = new GuiWelcomeStack(this);
  gui_settings_stack = new GuiSettingsStack_messaging(this);

  main_stacked_widget = new QStackedWidget(this);
  main_stacked_widget->addWidget(gui_welcome_stack);
  main_stacked_widget->addWidget(gui_settings_stack);
  main_stacked_widget->setCurrentWidget(gui_welcome_stack);

  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(main_stacked_widget);

}

GuiMainBlock::~GuiMainBlock()
{

}

/////////settings



/////////!settings


void GuiMainBlock::displayChatStack(QString usrKey)
{
  main_stacked_widget->setCurrentWidget(gui_chat_stack_map.find(usrKey).value());
}



void GuiMainBlock::displayStaticStack(StaticStackType staticStackType)
{
  switch (staticStackType) {
    case Home_Welcome:
      {
        gui_welcome_stack->refreshTime();
        main_stacked_widget->setCurrentWidget(gui_welcome_stack);

        break;
      }
    case Home_Storage:

      break;


    case Settings_Messaging:
      {
        main_stacked_widget->setCurrentWidget(gui_settings_stack);
        break;
      }
    case Settings_Profile:

      break;
    case Settings_Style:

      break;

    default:
      break;
    }
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

void GuiMainBlock::onColorDialogTriggered()
{

  QColor color = QColorDialog::getColor(Qt::white, this);
}


//  QProgressBar {
//      border: 1px solid #FFB500;
//      border-radius: 3px;
//      text-align: center;
//  }

//  QProgressBar::chunk {
//      background-color: #FFB500;

//  }
