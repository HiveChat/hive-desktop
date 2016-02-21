#include "GuiSettingsStack_messaging.h"

GuiSettingsStack_messaging::GuiSettingsStack_messaging(QWidget *parent)// : QWidget(parent)
{
  setIcon(":/img/img/messaging.png");
  setTitle("Settings");
  setSubTitle("messaging");

  QLabel *text_bubble_label = new QLabel("Text Bubble", this);
  QFont font("Futura");//Verdana
  font.setPointSize(15);
  text_bubble_label->setFont(font);
  text_bubble_label->setPalette(text_palette);

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(1);
  top_line->setFixedWidth(580);
  top_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: 0px transparent;  }");

  QLabel *in_bubble_label = new QLabel("\tReceived message bubble colour:", this);
  QFont sub_font("Futura");//Verdana
  in_bubble_label->setFont(sub_font);
  in_bubble_label->setPalette(sub_text_palette);
  GuiColorPicker *in_bubble_picker = new GuiColorPicker(&GlobalData::g_mChatBubbleColorI, this);
  QHBoxLayout *in_bubble_layout = new QHBoxLayout();
  in_bubble_layout->setContentsMargins(0,30,200,0);
  in_bubble_layout->setSpacing(30);
  in_bubble_layout->addWidget(in_bubble_label);
  in_bubble_layout->addWidget(in_bubble_picker);

  QLabel *out_bubble_label = new QLabel("\tSent message bubble colour:       ", this);
  out_bubble_label->setFont(sub_font);
  out_bubble_label->setPalette(sub_text_palette);
  GuiColorPicker *out_bubble_picker = new GuiColorPicker(&GlobalData::g_mChatBubbleColorO, this);
  QHBoxLayout *out_bubble_layout = new QHBoxLayout();
  out_bubble_layout->setContentsMargins(0,10,200,0);
  out_bubble_layout->setSpacing(30);
  out_bubble_layout->addWidget(out_bubble_label);
  out_bubble_layout->addWidget(out_bubble_picker);

  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->addWidget(text_bubble_label);
  central_layout->addWidget(top_line);
//  central_layout->addSpacing(15);
  central_layout->addLayout(in_bubble_layout);
  central_layout->addLayout(out_bubble_layout);

  this->setParent(parent);
}

GuiSettingsStack_messaging::~GuiSettingsStack_messaging()
{

}

