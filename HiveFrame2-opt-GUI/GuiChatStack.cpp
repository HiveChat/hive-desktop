#include "GuiChatStack.h"
#include <QLabel>
#include <QDebug>
#include <QPixmap>


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

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignCenter);
  main_layout->addWidget(top_bar);
  main_layout->addWidget(chat_scroll_area);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

}

GuiChatStack::~GuiChatStack()
{

}

//////////////////////////////////////////

GuiChatStack_top_bar::GuiChatStack_top_bar(QWidget *parent) : QWidget(parent)
{
  setAutoFillBackground(true);

  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, QColor(255,204,0,255));
  this->setPalette(palette);

  /*QPalette palette;
  palette.setColor(QPalette::Background, QColor(192,253,123));
  //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
  setPalette(palette);
///from baidu
*/

  avatar_label = new GuiTabLabel(this);
  avatar_label->setFixedHeight(50);
  avatar_label->setAlignment(Qt::AlignCenter);
  QPixmap avatar_pixmap("/Users/Echo/Desktop/4344.png");
  avatar_pixmap.setDevicePixelRatio(2.0);
  avatar_label->setPixmap(avatar_pixmap);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setMargin(0);
  main_layout->addWidget(avatar_label);


}

GuiChatStack_top_bar::~GuiChatStack_top_bar()
{

}

//////////////////////////////////////////

GuiChatStack_chat_widget::GuiChatStack_chat_widget(QWidget *parent) : QWidget(parent)
{

}

GuiChatStack_chat_widget::~GuiChatStack_chat_widget()
{

}

//////////////////////////////////////////

GuiChatStack_message_editor::GuiChatStack_message_editor(QWidget *parent) : QWidget(parent)
{
  text_editor = new QTextEdit(this);

  tool_layout = new QHBoxLayout();
  //tool_layout

  edit_layout = new QVBoxLayout();
  edit_layout->setAlignment(Qt::AlignTop);
  edit_layout->setMargin(0);
  edit_layout->setSpacing(0);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addLayout(edit_layout);

}

GuiChatStack_message_editor::~GuiChatStack_message_editor()
{

}
