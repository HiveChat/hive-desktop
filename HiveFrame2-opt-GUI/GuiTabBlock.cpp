#include "GuiTabBlock.h"
#include <QFileDialog>
#include <QLabel>

GuiTabBlock::GuiTabBlock(QWidget *parent) : QWidget(parent)
{
  this->setFixedWidth(200);

  ////label test
  /*QString fileName = QFileDialog::getOpenFileName(this,"Choose Image","x:/image",("Image File(*.*)")) ;
      QImage image ;
      image.load(fileName) ;

      QLabel *label = new QLabel();
      label->setPixmap(QPixmap::fromImage(image));
      label->resize(QSize(40,5));*/

  ////window btn
  exit_hint = new GuiTabLabel();
  min_hint = new GuiTabLabel();
  max_hint = new GuiTabLabel();

  exit_hint_img0.load(":/img/img/exit_hint_0.png");
  exit_hint_img0.setDevicePixelRatio(2.0);
  exit_hint_img1.load(":/img/img/exit_hint_1.png");
  exit_hint_img1.setDevicePixelRatio(2.0);
  exit_hint->setPixmap(exit_hint_img0);

  min_hint_img0.load(":/img/img/min_hint_0.png");
  min_hint_img0.setDevicePixelRatio(2.0);
  min_hint_img1.load(":/img/img/min_hint_1.png");
  min_hint_img1.setDevicePixelRatio(2.0);
  min_hint->setPixmap(min_hint_img0);

  max_hint_img0.load(":/img/img/max_hint_0.png");
  max_hint_img0.setDevicePixelRatio(2.0);
  max_hint_img1.load(":/img/img/max_hint_1.png");
  max_hint_img1.setDevicePixelRatio(2.0);
  max_hint->setPixmap(max_hint_img0);

  connect(exit_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
  connect(exit_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));
  connect(min_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
  connect(min_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));
  connect(max_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
  connect(max_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));

  ////window btn layout
  window_btn_layout = new QHBoxLayout();
  window_btn_layout->setMargin(10);
  window_btn_layout->setSpacing(8);
  window_btn_layout->setSizeConstraint(QLayout::SetFixedSize);
  window_btn_layout->setAlignment(Qt::AlignLeft);
  window_btn_layout->addWidget(exit_hint);
  window_btn_layout->addWidget(min_hint);
  window_btn_layout->addWidget(max_hint);

  ////tab label
  left_tab_label = new GuiTabLabel();
  mid_tab_label = new GuiTabLabel();
  right_tab_label = new GuiTabLabel();

  QPixmap left_label_img("/Users/Echo/Desktop/pp.png");//pp
  left_label_img.setDevicePixelRatio(2.0);
  left_tab_label->setPixmap(left_label_img);
  //left_tab_label->setScaledContents(true);
  //left_tab_label->resize(QSize(50,50));

  QPixmap mid_label_img("/Users/Echo/Desktop/t.png");//t
  mid_label_img.setDevicePixelRatio(2.0);
  mid_tab_label->setPixmap(mid_label_img);
  //mid_tab_label->setScaledContents(true);
  //mid_tab_label->resize(QSize(50,50));

  QPixmap right_label_img("/Users/Echo/Desktop/s.png");//s
  right_label_img.setDevicePixelRatio(2.0);
  right_tab_label->setPixmap(right_label_img);
  //right_tab_label->setScaledContents(true);
  //right_tab_label->resize(QSize(50,50));

  connect(left_tab_label, SIGNAL(clicked()), this, SLOT(changeBtnLine()));
  connect(mid_tab_label, SIGNAL(clicked()), this, SLOT(changeBtnLine()));
  connect(right_tab_label, SIGNAL(clicked()), this, SLOT(changeBtnLine()));

  ////tab line
  left_btn_line_label  = new QLabel();
  mid_btn_line_label   = new QLabel();
  right_btn_line_label = new QLabel();

  left_btn_line_label0.load(":/img/img/left_btn_line_label0.png");
  left_btn_line_label1.load(":/img/img/left_btn_line_label1.png");
  left_btn_line_label->setPixmap(QPixmap::fromImage(left_btn_line_label1));
  left_btn_line_label->resize(QSize(left_btn_line_label1.size()));

  mid_btn_line_label0.load(":/img/img/mid_btn_line_label0.png");
  mid_btn_line_label1.load(":/img/img/mid_btn_line_label1.png");
  mid_btn_line_label->setPixmap(QPixmap::fromImage(mid_btn_line_label0));
  mid_btn_line_label->resize(QSize(mid_btn_line_label0.size()));

  right_btn_line_label0.load(":/img/img/right_btn_line_label0.png");
  right_btn_line_label1.load(":/img/img/right_btn_line_label1.png");
  right_btn_line_label->setPixmap(QPixmap::fromImage(right_btn_line_label0));
  right_btn_line_label->resize(QSize(right_btn_line_label0.size()));


  ////tab label layout
  tab_label_layout = new QGridLayout();

  tab_label_layout->setMargin(10);
  tab_label_layout->setHorizontalSpacing(20);
  tab_label_layout->setVerticalSpacing(5);
  tab_label_layout->setAlignment(Qt::AlignTop);
  tab_label_layout->setSizeConstraint(QLayout::SetFixedSize);

  tab_label_layout->addWidget(left_tab_label,0,0,Qt::AlignCenter);
  tab_label_layout->addWidget(mid_tab_label,0,1,Qt::AlignCenter);
  tab_label_layout->addWidget(right_tab_label,0,2,Qt::AlignCenter);

  tab_label_layout->addWidget(left_btn_line_label,1,0,Qt::AlignCenter);
  tab_label_layout->addWidget(mid_btn_line_label,1,1,Qt::AlignCenter);
  tab_label_layout->addWidget(right_btn_line_label,1,2,Qt::AlignCenter);



  ////tab stacked widget
  gui_home_tab = new GuiHomeTab();
  gui_chat_tab = new GuiChatTab();

  tab_stacked_widget = new QStackedWidget(this);
  tab_stacked_widget->addWidget(gui_home_tab);
  tab_stacked_widget->addWidget(gui_chat_tab);

  //addWidget(QWidget*,int row,int column,int rowStretch,int columnStretch,Qt::Alignment)


  //// main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setSpacing(0);
  main_layout->setMargin(0);
  main_layout->setAlignment(Qt::AlignTop);
  //main_layout->setSizeConstraint(QLayout::SetFixedSize);
  main_layout->addLayout(window_btn_layout);
  main_layout->addLayout(tab_label_layout);
  main_layout->addWidget(tab_stacked_widget);
}

GuiTabBlock::~GuiTabBlock()
{

}

void GuiTabBlock::changeBtnLine()
{
  if(sender() == left_tab_label)
    {
      current_tab_index = 1;
      left_btn_line_label->setPixmap(QPixmap::fromImage(left_btn_line_label1));
      mid_btn_line_label->setPixmap(QPixmap::fromImage(mid_btn_line_label0));
      right_btn_line_label->setPixmap(QPixmap::fromImage(right_btn_line_label0));
      tab_stacked_widget->setCurrentWidget(gui_home_tab);
    }
  if(sender() == mid_tab_label)
    {
      current_tab_index = 2;
      left_btn_line_label->setPixmap(QPixmap::fromImage(left_btn_line_label0));
      mid_btn_line_label->setPixmap(QPixmap::fromImage(mid_btn_line_label1));
      right_btn_line_label->setPixmap(QPixmap::fromImage(right_btn_line_label0));
      tab_stacked_widget->setCurrentWidget(gui_chat_tab);
    }
  if(sender() == right_tab_label)
    {
      current_tab_index = 3;
      left_btn_line_label->setPixmap(QPixmap::fromImage(left_btn_line_label0));
      mid_btn_line_label->setPixmap(QPixmap::fromImage(mid_btn_line_label0));
      right_btn_line_label->setPixmap(QPixmap::fromImage(right_btn_line_label1));
    }
}

void GuiTabBlock::changeWindowBtn()
{
  exit_hint->setPixmap(exit_hint_img1);
  min_hint->setPixmap(min_hint_img1);
  max_hint->setPixmap(max_hint_img1);
}

void GuiTabBlock::recoverWindowBtn()
{
  exit_hint->setPixmap(exit_hint_img0);
  min_hint->setPixmap(min_hint_img0);
  max_hint->setPixmap(max_hint_img0);
}

int GuiTabBlock::currentIndex()
{
  return current_tab_index;
}

