#include "TabBlock.h"
#include <QFileDialog>
#include <QLabel>

TabBlock::TabBlock(QWidget *parent)
  : QWidget(parent)
  , home_tab(new HomeTab(this))
  , chat_tab(new ChatTab(this))
  , settings_tab(new SettingsTab(this))
  , tab_label_layout(new QGridLayout())
  , left_tab_label(new LabelButton(0, this))
  , mid_tab_label(new LabelButton(70, this))
  , right_tab_label(new LabelButton(0, this))
  , left_btn_line(new QFrame(this))
  , mid_btn_line(new QFrame(this))
  , right_btn_line(new QFrame(this))
  , tab_stacked_widget(new QStackedWidget(this))
{
  this->setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Window, Global::color_alphaTab);
  this->setPalette(palette);
  this->setFixedWidth(250);

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

  left_btn_line->setFrameShape(QFrame::HLine);
  left_btn_line->setFrameShadow(QFrame::Plain);
  left_btn_line->setFixedSize(83,2);
  left_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");

  mid_btn_line->setFrameShape(QFrame::HLine);
  mid_btn_line->setFrameShadow(QFrame::Plain);
  mid_btn_line->setFixedSize(84,3);
  mid_btn_line->setStyleSheet("QFrame{  background: #FFB500; border: transparent;  }");

  right_btn_line->setFrameShape(QFrame::HLine);
  right_btn_line->setFrameShadow(QFrame::Plain);
  right_btn_line->setFixedSize(83,2);
  right_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");

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

  tab_stacked_widget->addWidget(chat_tab);
  tab_stacked_widget->addWidget(home_tab);
  tab_stacked_widget->addWidget(settings_tab);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setSpacing(0);
  main_layout->setMargin(0);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addLayout(tab_label_layout);
  main_layout->addWidget(tab_stacked_widget);

  connect(left_tab_label,  &LabelButton::clicked, this, &TabBlock::changeBtnLine);
  connect(mid_tab_label,   &LabelButton::entered, this, &TabBlock::changeBtnLine);
  connect(right_tab_label, &LabelButton::clicked, this, &TabBlock::changeBtnLine);
}

TabBlock::~TabBlock()
{

}

void TabBlock::changeBtnLine()
{
  if(sender() == left_tab_label)
    {
      current_tab_index = 1;
      left_btn_line->setFixedHeight(3);
      left_btn_line->setStyleSheet("QFrame{  background: #FFB500; border: transparent;  }");
      mid_btn_line->setFixedHeight(2);
      mid_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");
      right_btn_line->setFixedHeight(2);
      right_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");
      tab_stacked_widget->setCurrentWidget(home_tab);
    }
  if(sender() == mid_tab_label)
    {
      current_tab_index = 2;
      left_btn_line->setFixedHeight(2);
      left_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");
      mid_btn_line->setFixedHeight(3);
      mid_btn_line->setStyleSheet("QFrame{  background: #FFB500; border: transparent;  }");
      right_btn_line->setFixedHeight(2);
      right_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");
      tab_stacked_widget->setCurrentWidget(chat_tab);
    }
  if(sender() == right_tab_label)
    {
      current_tab_index = 3;
      left_btn_line->setFixedHeight(2);
      left_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");
      mid_btn_line->setFixedHeight(2);
      mid_btn_line->setStyleSheet("QFrame{  background: #CFCFCF; border: transparent;  }");
      right_btn_line->setFixedHeight(3);
      right_btn_line->setStyleSheet("QFrame{  background: #FFB500; border: transparent;  }");
      tab_stacked_widget->setCurrentWidget(settings_tab);
    }
}

