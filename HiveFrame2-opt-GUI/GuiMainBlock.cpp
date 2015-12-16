#include "GuiMainBlock.h"
#include <QPalette>
#include <QPainter>

GuiMainBlock::GuiMainBlock(QWidget *parent) : QWidget(parent)
{
  gui_chat_stack = new GuiChatStack(this);

  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(gui_chat_stack);
}

GuiMainBlock::~GuiMainBlock()
{

}

