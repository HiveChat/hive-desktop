#include "GuiChatTab.h"
#include <QApplication>
#include <QMenu>
#include <QDebug>
#include <QScrollBar>

GuiChatTab::GuiChatTab(QWidget *parent) : QWidget(parent)
{

  comb_scrollarea = new QScrollArea(this);
  comb_scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  comb_scrollarea->setFrameShape(QFrame::NoFrame);
  comb_scrollarea->setWidgetResizable(true);
  comb_scroll_widget = new GuiChatTab_comb_scroll_widget();
  comb_scrollarea->setWidget(comb_scroll_widget);

  /*comb_treewidget = new QTreeWidget(this);
  comb_treewidget->setHeaderHidden(true);
  comb_treewidget->setAnimated(true);
  comb_treewidget->setAlternatingRowColors(false);
  comb_treewidget->setFrameStyle(QFrame::NoFrame);

  connect(comb_treewidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onItemClicked(QTreeWidgetItem*, int)));

  QTreeWidgetItem *item=new QTreeWidgetItem(comb_treewidget,QStringList(QString("Tree")));//添加节点
      //添加子节点


  for(int i = 0; i <= 10; i++)
    {
      QTreeWidgetItem *item1=new QTreeWidgetItem(item,QStringList(QString("Band")+QString::number(i+1)));
      item->addChild(item1);
    }
  //comb_treewidget->setFixedWidth(100);
  */

  ////main layout

  main_layout = new QVBoxLayout(this);
  main_layout->addWidget(comb_scrollarea);

  main_layout->setContentsMargins(5,5,5,5);

  QPalette palette;
  palette.setColor(QPalette::Window, GlobalData::color_tab);

  this->setAutoFillBackground(true);
  this->setPalette(palette);
  this->setFixedWidth(250);
}



void GuiChatTab::showMenu()
{
    /*QPoint pos;
    //QMenu menu(comb_treewidget);
    QIcon myIcon(":/GuiTabBlock/right_btn_line_label1.png");
    menu.addAction(myIcon,tr("菜单_1"));
    menu.addAction(myIcon,tr("菜单_2"));
    menu.addAction(myIcon,tr("菜单_3"));
    menu.addAction(myIcon,tr("菜单_4"));
    menu.addAction(myIcon,tr("菜单_5"));
    menu.addAction(myIcon,tr("菜单_6"));
    menu.exec(QCursor::pos());*/
}


//////////////////////////////////////////////////////////////////////////////////////////////////

GuiChatTab_comb_scroll_widget::GuiChatTab_comb_scroll_widget(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window,QColor(0,0,0,0));// GlobalData::g_tabColor);
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  ///main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);

}

void GuiChatTab_comb_scroll_widget::addComb(UsrProfileStruct *usrProfileStruct)
{
  qDebug()<<"#GuiChatTab_comb_scroll_widget::addComb(): Adding Comb.";
  GuiCombWidget *comb_widget = new GuiCombWidget(usrProfileStruct, this);
  comb_widget_map.insert(usrProfileStruct->key_str, comb_widget);
  main_layout->addWidget(comb_widget);
  connect(comb_widget, SIGNAL(clicked(QString)), this, SLOT(onCombWidgetClicked(QString)));
}

void GuiChatTab_comb_scroll_widget::setBadgeNumber(const QString &usrKey, const int &num)
{
  comb_widget_map.value(usrKey)->setBadgeNumber(num);
}

void GuiChatTab_comb_scroll_widget::refreshComb(UsrProfileStruct *usrProfileStruct)
{
  GlobalData::TEST_printUsrProfileStruct(*usrProfileStruct, "comb scroll widget");
  GuiCombWidget *comb_widget = comb_widget_map.value(usrProfileStruct->key_str);
  if(comb_widget != nullptr)
    {
      comb_widget->setProfile(usrProfileStruct);
    }
  else
    {
      qDebug()<<"Something Impossible happened!!!";
    }
}

void GuiChatTab_comb_scroll_widget::onCombWidgetClicked(QString usrKey)
{
  emit combWidgetClicked(usrKey);
}
