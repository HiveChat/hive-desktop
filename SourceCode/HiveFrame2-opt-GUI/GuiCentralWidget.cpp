#include "GuiCentralWidget.h"
#include <QIcon>

GuiCentralWidget::GuiCentralWidget(QWidget *parent) : QWidget(parent)
{

  ////data manager
  data_manager = new DataManager(this);

  ////net manager
  net_manager = new NetManager(this);

  ////Gui
  gui_tab_block = new GuiTabBlock(this);
  gui_main_block = new GuiMainBlock(this);

  QFrame *line = new QFrame(this);
  line->setFrameShape(QFrame::VLine);
  line->setFrameShadow(QFrame::Plain);
  line->setStyleSheet ("QFrame{  background: #efefef; border: 1px transparent;  }");

  //main_layout
  main_layout = new QHBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(gui_tab_block);
  main_layout->addWidget(line);
  main_layout->addWidget(gui_main_block);

  //connect
  connect(gui_tab_block->gui_chat_tab->comb_scroll_widget, SIGNAL(combWidgetClicked(QString)), gui_main_block, SLOT(displayChatStack(QString)));
  connect(gui_tab_block->gui_home_tab->welcome_label, SIGNAL(clicked()), gui_main_block, SLOT(displayWelcomeStack()));

  //connect(gui_tab_block->gui_chat_tab->comb_scroll_widget, SIGNAL(combWidgetClicked(QString)), data_manager, SLOT(readMessage(QString)));
  //connect(gui_tab_block->gui_chat_tab->comb_scroll_widget, SIGNAL(combWidgetClicked(QString)), gui_main_block->gui_chat_stack, SLOT(checkIdentity(QStringList)));





  ///data:
  connect(data_manager, SIGNAL(usrProfileLoaded(QStringList)), gui_tab_block->gui_chat_tab->comb_scroll_widget, SLOT(addComb(QStringList)));
  connect(data_manager, SIGNAL(usrProfileLoaded(QStringList)), gui_main_block, SLOT(addChatStack(QStringList)));

  data_manager->loadUsrProfile();



  ////net manager
  connect(net_manager, SIGNAL(messageRecieved(QStringList)), gui_main_block, SLOT(onMessageRecieved(QStringList)));


  ////dynamic widgets


  this->setParent(parent);
}

GuiCentralWidget::~GuiCentralWidget()
{
  qDebug()<<"\n@Hive is destructed";

}






/*void GuiCentralWidget::initUsrData()
{

}*/
