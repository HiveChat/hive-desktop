#include "GuiCentralWidget.h"
#include <QIcon>

GuiCentralWidget::GuiCentralWidget(QWidget *parent) : QWidget(parent)
{
  gui_tab_block = new GuiTabBlock(this);
  gui_main_block = new GuiMainBlock(this);

  /*QFrame *line = new QFrame(this);
  line->setFrameShape(QFrame::VLine);
  line->setFrameShadow(QFrame::Plain);
  line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");*/

  ////main_layout
  main_layout = new QHBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(gui_tab_block);
  //main_layout->addWidget(line);
  main_layout->addWidget(gui_main_block);

  data_manager = new DataManager(this);
  connect(data_manager, SIGNAL(onUsrProfileLoaded(QStringList)), gui_tab_block->gui_chat_tab->comb_scroll_widget, SLOT(addComb(QStringList)));
  data_manager->loadUsrProfile();
  gui_main_block->gui_chat_stack->chat_widget->addChatBubble("Once the  to be inflated to open the root,the  on the non-breaking is not to squeeze,and this is a tragedy.Found in Hamlet,the vulnerability of people and the environment is so brutal and contrary to each other,as well as the unique aspects of the character appears in the connotations of dense and thick,it is also in the extension of broad and deep.By doing so,some experts have claimed that Hamlet is not an objective of the role of out-of-date,but each of us own.");

}

GuiCentralWidget::~GuiCentralWidget()
{

}

/*void GuiCentralWidget::initUsrData()
{

}*/
