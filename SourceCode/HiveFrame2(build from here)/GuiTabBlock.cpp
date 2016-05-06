#include "GuiTabBlock.h"
#include <QFileDialog>
#include <QLabel>

GuiTabBlock::GuiTabBlock(QWidget *parent) : QWidget(parent)
{
  this->setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Window, GlobalData::g_alphaTabColor);
  this->setPalette(palette);
  this->setFixedWidth(250);

  ////label test
  /// QFileDialog Example
//  QString fileName = QFileDialog::getOpenFileName(this,"Choose Image","/",("Image File(*.*)")) ;
//      QImage image ;
//      image.load(fileName) ;

  ////window btn
//  exit_hint = new GuiLabelButton(this);
//  min_hint = new GuiLabelButton(this);
//  max_hint = new GuiLabelButton(this);

//  exit_hint->setDefaultPixmap(":/img/img/exit_hint_0.png");
//  exit_hint->setHoveredPixmap(":/img/img/exit_hint_1.png");

//  min_hint->setDefaultPixmap(":/img/img/min_hint_0.png");
//  min_hint->setHoveredPixmap(":/img/img/min_hint_1.png");

//  max_hint->setDefaultPixmap(":/img/img/max_hint_0.png");
//  max_hint->setHoveredPixmap(":/img/img/max_hint_1.png");

//  connect(exit_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
//  connect(exit_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));
//  connect(min_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
//  connect(min_hintr, SIGNAL(left()), this, SLOT(recoverWindowBtn()));
//  connect(max_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
//  connect(max_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));

//  ////window btn layout
//  window_btn_layout = new QHBoxLayout();
//  window_btn_layout->setMargin(10);
//  window_btn_layout->setSpacing(8);
//  window_btn_layout->setSizeConstraint(QLayout::SetFixedSize);
//  window_btn_layout->setAlignment(Qt::AlignLeft);
//  window_btn_layout->addWidget(exit_hint);
//  window_btn_layout->addWidget(min_hint);
//  window_btn_layout->addWidget(max_hint);

  ////tab label
  left_tab_label = new GuiLabelButton(this);
  mid_tab_label = new GuiLabelButton(this);
  right_tab_label = new GuiLabelButton(this);

  left_tab_label->setDefaultPixmap(":/img/img/home_tab.png");
  left_tab_label->setHoveredPixmap(":/img/img/home_tab.png");
  left_tab_label->setToolTipDuration(1000);
  left_tab_label->setToolTip("home");

  mid_tab_label->setDefaultPixmap(":/img/img/chat_tab.png");
  mid_tab_label->setHoveredPixmap(":/img/img/chat_tab.png");
  mid_tab_label->setToolTipDuration(1000);
  mid_tab_label->setToolTip("chat");

  right_tab_label->setDefaultPixmap(":/img/img/settings_tab.png");
  right_tab_label->setHoveredPixmap(":/img/img/settings_tab.png");
  right_tab_label->setToolTipDuration(1000);
  right_tab_label->setToolTip("settings");

  connect(left_tab_label, SIGNAL(clicked()), this, SLOT(changeBtnLine()));
  connect(mid_tab_label, SIGNAL(clicked()), this, SLOT(changeBtnLine()));
  connect(right_tab_label, SIGNAL(clicked()), this, SLOT(changeBtnLine()));

  ////tab line
  left_btn_line  = new QFrame(this);
  mid_btn_line   = new QFrame(this);
  right_btn_line = new QFrame(this);

  left_btn_line->setFrameShape(QFrame::HLine);
  left_btn_line->setFrameShadow(QFrame::Plain);
  left_btn_line->setFixedSize(83,3);
  left_btn_line->setStyleSheet ("QFrame{  background: #FFB500; border: transparent;  }");

  mid_btn_line->setFrameShape(QFrame::HLine);
  mid_btn_line->setFrameShadow(QFrame::Plain);
  mid_btn_line->setFixedSize(84,2);
  mid_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");

  right_btn_line->setFrameShape(QFrame::HLine);
  right_btn_line->setFrameShadow(QFrame::Plain);
  right_btn_line->setFixedSize(83,2);
  right_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");

  ////tab label layout
  tab_label_layout = new QGridLayout();

  tab_label_layout->setContentsMargins(0,10,0,10);
  tab_label_layout->setHorizontalSpacing(0);
  tab_label_layout->setVerticalSpacing(7);
  tab_label_layout->setAlignment(Qt::AlignTop);
  tab_label_layout->setSizeConstraint(QLayout::SetFixedSize);

  tab_label_layout->addWidget(left_tab_label,0,0,Qt::AlignCenter);
  tab_label_layout->addWidget(mid_tab_label,0,1,Qt::AlignCenter);
  tab_label_layout->addWidget(right_tab_label,0,2,Qt::AlignCenter);

  tab_label_layout->addWidget(left_btn_line,1,0,Qt::AlignLeft);
  tab_label_layout->addWidget(mid_btn_line,1,1,Qt::AlignCenter);
  tab_label_layout->addWidget(right_btn_line,1,2,Qt::AlignRight);



  ////tab stacked widget
  gui_home_tab = new GuiHomeTab();
  gui_chat_tab = new GuiChatTab();
  gui_settings_tab = new GuiSettingsTab();

  tab_stacked_widget = new QStackedWidget(this);
  tab_stacked_widget->addWidget(gui_home_tab);
  tab_stacked_widget->addWidget(gui_chat_tab);
  tab_stacked_widget->addWidget(gui_settings_tab);

  //// main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setSpacing(0);
  main_layout->setMargin(0);
  main_layout->setAlignment(Qt::AlignTop);
  //main_layout->addLayout(window_btn_layout);
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
      left_btn_line->setFixedHeight(3);
      left_btn_line->setStyleSheet ("QFrame{  background: #FFB500; border: transparent;  }");
      mid_btn_line->setFixedHeight(2);
      mid_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");
      right_btn_line->setFixedHeight(2);
      right_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");
      tab_stacked_widget->setCurrentWidget(gui_home_tab);
    }
  if(sender() == mid_tab_label)
    {
      current_tab_index = 2;
      left_btn_line->setFixedHeight(2);
      left_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");
      mid_btn_line->setFixedHeight(3);
      mid_btn_line->setStyleSheet ("QFrame{  background: #FFB500; border: transparent;  }");
      right_btn_line->setFixedHeight(2);
      right_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");
      tab_stacked_widget->setCurrentWidget(gui_chat_tab);
    }
  if(sender() == right_tab_label)
    {
      current_tab_index = 3;
      left_btn_line->setFixedHeight(2);
      left_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");
      mid_btn_line->setFixedHeight(2);
      mid_btn_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: transparent;  }");
      right_btn_line->setFixedHeight(3);
      right_btn_line->setStyleSheet ("QFrame{  background: #FFB500; border: transparent;  }");
      tab_stacked_widget->setCurrentWidget(gui_settings_tab);

    }
}

//void GuiTabBlock::changeWindowBtn()
//{
//  exit_hint->setHovered();
//  min_hint->setHovered();
//  max_hint->setHovered();
//}

//void GuiTabBlock::recoverWindowBtn()
//{
//  exit_hint->setDefault();
//  min_hint->setDefault();
//  max_hint->setDefault();
//}

int GuiTabBlock::currentIndex()
{
  return current_tab_index;
}

