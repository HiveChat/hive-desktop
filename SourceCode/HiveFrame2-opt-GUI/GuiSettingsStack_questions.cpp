#include "GuiSettingsStack_questions.h"


GuiSettingsStack_questions::GuiSettingsStack_questions(QWidget *parent)// : QWidget(parent)
{
  setIcon(":/img/img/question.png");
  setTitle("Settings");
  setSubTitle("questions");

  QLabel *text_bubble_label = new QLabel("About Hive", this);
  text_bubble_label->setFont(font);
  text_bubble_label->setPalette(text_palette);

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(1);
  top_line->setFixedWidth(580);
  top_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: 0px transparent;  }");

  QLabel *author_label = new QLabel("Author:", this);
  author_label->setFont(sub_font);
  author_label->setPalette(sub_text_palette);

  QHBoxLayout *in_bubble_layout = new QHBoxLayout();
  in_bubble_layout->setContentsMargins(0,30,200,0);
  in_bubble_layout->setSpacing(30);
  in_bubble_layout->addWidget(author_label);

  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->setContentsMargins(0,30,0,50);
  central_layout->addWidget(text_bubble_label);
  central_layout->addWidget(top_line);
//  central_layout->addSpacing(15);
  central_layout->addLayout(in_bubble_layout);

  this->setParent(parent);
}

GuiSettingsStack_questions::~GuiSettingsStack_questions()
{

}

