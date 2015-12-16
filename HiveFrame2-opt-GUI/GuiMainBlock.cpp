#include "GuiMainBlock.h"
#include <QPalette>
#include <QPainter>

GuiMainBlock::GuiMainBlock(QWidget *parent) : QWidget(parent)
{
  gui_chat_stack = new GuiChatStack(this);
  gui_welcome_stack = new GuiWelcomeStack(this);

  main_stacked_widget = new QStackedWidget(this);
  main_stacked_widget->addWidget(gui_welcome_stack);
  main_stacked_widget->addWidget(gui_chat_stack);
  main_stacked_widget->setCurrentWidget(gui_chat_stack);

  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(main_stacked_widget);
}

GuiMainBlock::~GuiMainBlock()
{

}

