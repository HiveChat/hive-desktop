#include "GuiCentralWidget.h"

GuiCentralWidget::GuiCentralWidget(QWidget *parent) : QWidget(parent)
{
//! do not delete yet, see if it causes problems.
//  QPalette palette;
//  palette.setColor(QPalette::Window, QColor(250,250,250));
//  this->setPalette(palette);

  this->setMinimumHeight(600);
  this->setMinimumWidth(900);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowTitle(QString("Hive! %1.%2.%3 alpha-test")
                       .arg(GlobalData::g_version[0])
                       .arg(GlobalData::g_version[1])
                       .arg(GlobalData::g_version[2]));

  ////Gui
  gui_tab_block = new GuiTabBlock(this);
  gui_main_block = new GuiMainBlock(this);

  QFrame *line = new QFrame(this);
  line->setFrameShape(QFrame::VLine);
  line->setFrameShadow(QFrame::Plain);
  line->setFixedWidth(1);
  line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");

  //main_layout
  main_layout = new QHBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(gui_tab_block);
  main_layout->addWidget(line);
  main_layout->addWidget(gui_main_block);

  //connect
  connect(gui_tab_block->gui_chat_tab->comb_scroll_widget, SIGNAL(combWidgetClicked(QString)), gui_main_block, SLOT(displayChatStack(QString)));

  ///buttons~~
  connect(gui_tab_block->gui_home_tab->welcome_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_home_tab->list_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_home_tab->storage_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));

  connect(gui_tab_block->gui_settings_tab->messaging_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_settings_tab->profile_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_settings_tab->questions_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));



}

GuiCentralWidget::~GuiCentralWidget()
{
  qDebug()<<"\n@Hive UI is destructed";
}


void GuiCentralWidget::addUsr(UsrProfileStruct *usrProfileStruct)
{
  gui_tab_block->gui_chat_tab->comb_scroll_widget->addComb(usrProfileStruct);
  gui_main_block->addChatStack(usrProfileStruct);
  gui_main_block->gui_home_stack_list->addUsr(usrProfileStruct);
}

void GuiCentralWidget::delUsr(UsrProfileStruct *usrProfileStruct)
{

}

void GuiCentralWidget::changeUsr(UsrProfileStruct *usrProfileStruct)
{
  gui_main_block->gui_chat_stack_map.value(usrProfileStruct->key_str)->refreshUsrProfile(usrProfileStruct);
  gui_tab_block->gui_chat_tab->comb_scroll_widget->refreshComb(usrProfileStruct);
  gui_main_block->gui_home_stack_list->refreshUsrProfile(usrProfileStruct);
}

