#include "GuiChatStack.h"
#include <QLabel>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>

#include <QScrollBar>
#include <QBitmap>
#include <QPainter>

#include <GuiButton.h>

//////////////////////////top//////////////////////////////////////

GuiChatStack_top_bar::GuiChatStack_top_bar(QWidget *parent) : QWidget(parent)
{
  setAutoFillBackground(true);
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, QColor(255,197,28,100));
  this->setPalette(palette);

  /*QPalette palette;
  palette.setColor(QPalette::Background, QColor(192,253,123));
  //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
  setPalette(palette);
///from baidu
*/

  avatar_label = new GuiAvatarButton("/Users/Echo/Desktop/squirrel.jpg", 90, 90, this);
  avatar_label->setFixedHeight(50);
  avatar_label->setAlignment(Qt::AlignLeft);

  //
  QLabel *usr_name_label = new QLabel("@Echo Zheng");
  QLabel *usr_ip_label = new QLabel("192.168.1.1");

  QFont usr_name_font("Verdana");
  usr_name_font.setPixelSize(15);
  usr_name_label->setFont(usr_name_font);

  QFont usr_ip_font("Gill Sans");
  usr_ip_font.setPixelSize(11);
  usr_ip_label->setFont(usr_ip_font);

  QVBoxLayout *usr_info_layout = new QVBoxLayout();
  usr_info_layout->setContentsMargins(0,0,10,10);
  usr_info_layout->addWidget(usr_name_label);
  usr_info_layout->addWidget(usr_ip_label);


  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->setContentsMargins(15,10,10,0);
  main_layout->setSpacing(10);
  main_layout->addWidget(avatar_label);
  main_layout->addLayout(usr_info_layout);


}

GuiChatStack_top_bar::~GuiChatStack_top_bar()
{

}

//////////////////////////mid//////////////////////////////////////

GuiChatStack_chat_widget::GuiChatStack_chat_widget(QWidget *parent) : QWidget(parent)
{
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0,10,10,10);


  GuiButton *buttonf;

  for(int i = 0; i < 2; i++)
    {
      gui_chat_bubble = new GuiChatBubble("Copyright (C) 2007 Free Software Foundation, Inc. [http://fsf.org/]Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.",300,this);
      main_layout->addWidget(gui_chat_bubble);
    }

}

GuiChatStack_chat_widget::~GuiChatStack_chat_widget()
{

}

//////////////////////////bottom//////////////////////////////////////

GuiChatStack_message_editor::GuiChatStack_message_editor(QWidget *parent) : QWidget(parent)
{
  this->setMaximumHeight(150);
  text_editor = new QTextEdit(this);
  text_editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  text_editor->setFrameStyle(QFrame::NoFrame);

  QFont text_font("Gill Sans", 34);
  text_font.setPixelSize(16);
  text_editor->setFont(text_font);

  ///tools
  expression_label = new GuiLabelButton(this);
  image_label = new GuiLabelButton(this);
  file_label = new GuiLabelButton(this);

  expression_label->setDefaultPixmap(":/img/img/expression_label_0.png");
  expression_label->setHoveredPixmap(":/img/img/expression_label_1.png");
  //expression_label->setAlignment(Qt::AlignLeft);

  image_label->setDefaultPixmap(":/img/img/image_label_0.png");
  image_label->setHoveredPixmap(":/img/img/image_label_1.png");
  //image_label->setAlignment(Qt::AlignLeft);

  file_label->setDefaultPixmap(":/img/img/file_label_0.png");
  file_label->setHoveredPixmap(":/img/img/file_label_1.png");
  //file_label->setAlignment(Qt::AlignLeft);

  tool_layout = new QHBoxLayout();
  tool_layout->setAlignment(Qt::AlignLeft);
  tool_layout->setContentsMargins(0,5,5,5);
  tool_layout->setSpacing(15);
  tool_layout->addWidget(expression_label);
  tool_layout->addWidget(image_label);
  tool_layout->addWidget(file_label);

  edit_layout = new QVBoxLayout();
  edit_layout->setAlignment(Qt::AlignLeft);
  edit_layout->setContentsMargins(10,5,15,10);
  edit_layout->setSpacing(5);
  edit_layout->addLayout(tool_layout);
  edit_layout->addWidget(text_editor);

  ///send button
  send_btn = new GuiLabelButton();
  send_btn->setDefaultPixmap(":/img/img/send_button_0.png");
  send_btn->setHoveredPixmap(":/img/img/send_button_0.png");
  send_btn->setPressedPixmap(":/img/img/send_button_1.png");
  send_btn->setAlignment(Qt::AlignRight);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setContentsMargins(0,0,20,0);
  main_layout->setSpacing(0);
  main_layout->addLayout(edit_layout);
  main_layout->addWidget(send_btn);

}

GuiChatStack_message_editor::~GuiChatStack_message_editor()
{

}

//////////////////////////main//////////////////////////////////////

GuiChatStack::GuiChatStack(QWidget *parent) : QWidget(parent)
{
  top_bar = new GuiChatStack_top_bar(this);

  chat_widget = new GuiChatStack_chat_widget(this);
  chat_scroll_area = new QScrollArea(this);
  chat_scroll_area->setWidget(chat_widget);

  QPalette palette = chat_scroll_area->palette();
  palette.setColor(QPalette::Base, QColor(255,255,255,255));
  chat_scroll_area->setPalette(palette);

  chat_scroll_area->setFrameStyle(0);

  message_editor = new GuiChatStack_message_editor(this);

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignCenter);
  main_layout->addWidget(top_bar);
  main_layout->addWidget(chat_scroll_area);
  main_layout->addWidget(message_editor);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

}

GuiChatStack::~GuiChatStack()
{

}
