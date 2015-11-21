#include "GuiCentralWidget.h"
#include <QIcon>

GuiCentralWidget::GuiCentralWidget(QWidget *parent) : QWidget(parent)
{
  gui_tab_block = new GuiTabBlock(this);
  gui_main_block = new GuiMainBlock(this);

  ////main_layout
  main_layout = new QHBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(gui_tab_block);
  main_layout->addWidget(gui_main_block);

}

GuiCentralWidget::~GuiCentralWidget()
{

}

