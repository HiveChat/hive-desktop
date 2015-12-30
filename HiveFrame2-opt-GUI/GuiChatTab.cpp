#include "GuiChatTab.h"
#include <QApplication>
#include <QMenu>
#include <QDebug>

GuiChatTab::GuiChatTab(QWidget *parent) : QWidget(parent)
{
  comb_scrollarea = new QScrollArea(this);

  comb_scrollarea->setFrameShape(QFrame::NoFrame);
  comb_scrollarea->setWidgetResizable(true);
  QPalette comb_scrollarea_palette;
  comb_scrollarea_palette.setColor(QPalette::Background, Qt::white);
  comb_scrollarea->setPalette(comb_scrollarea_palette);

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

}



void GuiChatTab::onItemClicked(QTreeWidgetItem *item, int column)
{

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
  QPalette comb_scroll_widget_palette;
  comb_scroll_widget_palette.setColor(QPalette::Background, Qt::white);
  this->setPalette(comb_scroll_widget_palette);

  ///main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);

  this->setParent(parent);


}

void GuiChatTab_comb_scroll_widget::addComb(QStringList usrInfoStrList)
{
  qDebug()<<"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh";
  GuiCombWidget *gui_comb_widget = new GuiCombWidget(usrInfoStrList, this);
  main_layout->addWidget(gui_comb_widget);
}
