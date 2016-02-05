#include "GuiMainBlock.h"
#include <QPalette>
#include <QPainter>

GuiMainBlock::GuiMainBlock(QWidget *parent) : QWidget(parent)
{

//  QPalette palette;
//  //255,204,0,255
//  palette.setColor(QPalette::Window, QColor(245,245,245));
//  this->setAutoFillBackground(true);
//  this->setPalette(palette);

  gui_welcome_stack = new GuiWelcomeStack(this);

  main_stacked_widget = new QStackedWidget(this);
  main_stacked_widget->addWidget(gui_welcome_stack);
  main_stacked_widget->setCurrentWidget(gui_welcome_stack);

  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(main_stacked_widget);

}

GuiMainBlock::~GuiMainBlock()
{

}

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

  connect(this, SIGNAL(whoseMessage(QStringList)), gui_chat_stack, SLOT(checkMessage(QStringList)));
}

void GuiMainBlock::onMessageRecieved(QStringList message_str_list)
{
  //problem here
  //gui_chat_stack_map.find(message_str_list[0]).value()->checkMessage(message_str_list);
  emit whoseMessage(message_str_list);
}




