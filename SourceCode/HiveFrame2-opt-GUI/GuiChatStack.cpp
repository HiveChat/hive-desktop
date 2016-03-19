#include "GuiChatStack.h"

//////////////////////////top//////////////////////////////////////
GuiChatStack_top_bar::GuiChatStack_top_bar(UsrProfileStruct *usrProfileStruct, QWidget *parent) : QWidget(parent)
{
  ///usrKey<<usrName<<ipAddr<<avatarPathr
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  avatar_button = new GuiAvatarButton(usrProfileStruct->avatar_str, 90, this);
  avatar_button->setAlignment(Qt::AlignLeft);

  QLabel *usr_name_label = new QLabel(usrProfileStruct->name_str, this);
  QLabel *usr_ip_label = new QLabel(usrProfileStruct->ip_str, this);

  QFont usr_name_font("Futura");//Verdana
  usr_name_font.setPointSize(15);
  usr_name_label->setFont(usr_name_font);

  QFont usr_ip_font("Futura");//Gill Sans
  usr_ip_font.setPointSize(11);
  usr_ip_label->setFont(usr_ip_font);

  QVBoxLayout *usr_info_layout = new QVBoxLayout();
  usr_info_layout->setContentsMargins(0,0,10,10);
  usr_info_layout->addWidget(usr_name_label);
  usr_info_layout->addWidget(usr_ip_label);


  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->setContentsMargins(15,10,10,0);
  main_layout->setSpacing(10);
  main_layout->addWidget(avatar_button);
  main_layout->addLayout(usr_info_layout);

  this->setFixedHeight(69);



}

GuiChatStack_top_bar::~GuiChatStack_top_bar()
{

}

//////////////////////////mid//////////////////////////////////////

GuiChatStack_chat_widget::GuiChatStack_chat_widget(QWidget *parent) : QWidget(parent)
{
  setAutoFillBackground(true);
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);

  chat_bubble_layout = new QVBoxLayout();
  chat_bubble_layout->setAlignment(Qt::AlignTop);
  chat_bubble_layout->addStretch();
  chat_bubble_layout->setContentsMargins(5,30,5,30);

  ///lines
  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(2);
  top_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  QFrame *bottom_line = new QFrame(this);
  bottom_line->setFrameShape(QFrame::HLine);
  bottom_line->setFrameShadow(QFrame::Plain);
  bottom_line->setFixedHeight(4);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setSpacing(5);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->addWidget(top_line);
  main_layout->addLayout(chat_bubble_layout);
  main_layout->addWidget(bottom_line);


}

GuiChatStack_chat_widget::~GuiChatStack_chat_widget()
{

}

void GuiChatStack_chat_widget::clearChatBubbles()
{
  foreach (GuiChatBubble *temp_chat_bubble_pointer, chat_bubble_list)
    {
      temp_chat_bubble_pointer->deleteLater();
    }
}

void GuiChatStack_chat_widget::addChatBubble(QString message, bool fromMe)
{
  gui_chat_bubble = new GuiChatBubble(message, !fromMe, this);
  if(fromMe)
    {
      chat_bubble_layout->addWidget(gui_chat_bubble/*, Qt::AlignRight*/);
    }
  else
    {
      chat_bubble_layout->addWidget(gui_chat_bubble/*, Qt::AlignLeft*/);
    }
  chat_bubble_list.append(gui_chat_bubble);
}

//////////////////////////bottom//////////////////////////////////////

GuiChatStack_message_editor::GuiChatStack_message_editor(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  text_editor = new QTextEdit(this);
  text_editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  text_editor->setFrameStyle(QFrame::NoFrame);

  QFont text_font("Gill Sans", 34);
  text_font.setPointSize(16);
  text_editor->setFont(text_font);

  ///tools
  expression_label = new GuiLabelButton(this);
  image_label = new GuiLabelButton(this);
  file_label = new GuiLabelButton(this);

  expression_label->setDefaultPixmap(":/img/img/expression_label_0.png");
  expression_label->setHoveredPixmap(":/img/img/expression_label_1.png");

  image_label->setDefaultPixmap(":/img/img/image_label_0.png");
  image_label->setHoveredPixmap(":/img/img/image_label_1.png");

  file_label->setDefaultPixmap(":/img/img/file_label_0.png");
  file_label->setHoveredPixmap(":/img/img/file_label_1.png");

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
  send_btn->setHoveredPixmap(":/img/img/send_button_1.png");
  //send_btn->setPressedPixmap(":/img/img/send_button_1.png");
  send_btn->setAlignment(Qt::AlignRight);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setContentsMargins(0,0,20,0);
  main_layout->setSpacing(0);
  main_layout->addLayout(edit_layout);
  main_layout->addWidget(send_btn);


  this->setMaximumHeight(130);
  this->setParent(parent);
}

GuiChatStack_message_editor::~GuiChatStack_message_editor()
{

}

void GuiChatStack_message_editor::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Enter)
    {
      //send_btn->setHovered();
      ////emit send!
    }
}

void GuiChatStack_message_editor::keyReleaseEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Enter)
    {
      send_btn->setDefault();
      ////emit send!
    }
}
//////////////////////////main//////////////////////////////////////

GuiChatStack::GuiChatStack(UsrProfileStruct *usrProfileStruct, QWidget *parent) : QWidget(parent)
{
  ///Data
  usr_profile = *usrProfileStruct;

  data_history_io = new DataHistoryIO(usr_profile.key_str, this);
  refreshCurrentActiveIndex();

  ///UI
  top_bar = new GuiChatStack_top_bar(&usr_profile, this);

  QFrame *top_bar_line = new QFrame(this);
  top_bar_line->setFrameShape(QFrame::HLine);
  top_bar_line->setFrameShadow(QFrame::Plain);
  top_bar_line->setFixedHeight(2);
  top_bar_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  chat_widget = new GuiChatStack_chat_widget(this);
  chat_scroll_area = new QScrollArea(this);
  chat_scroll_area->setWidgetResizable(true);
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
  main_layout->addWidget(top_bar_line);
  main_layout->addWidget(chat_scroll_area);
  main_layout->addWidget(message_editor);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

  connect(message_editor->send_btn, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));

  loadHistory(current_active_index);

  this->setParent(parent);



  chat_widget->addChatBubble("mou", true);
}

GuiChatStack::~GuiChatStack()
{

}

void GuiChatStack::refreshCurrentActiveIndex()
{
  current_active_index = data_history_io->currentActiveIndex();
}


///slots


void GuiChatStack::checkMessage(QStringList message_str_list, bool fromMe)
{
//  QString object_key_str;//0 receiver
//  QString subject_key_str;//1 sender
//  QString message_str;//2
  qDebug()<<"wait!!here!!!";
  chat_widget->addChatBubble(message_str_list[2], fromMe);

  data_history_io->wirteMessage(message_str_list, fromMe);

  refreshCurrentActiveIndex();

  chat_scroll_area->verticalScrollBar()->setValue(chat_scroll_area->verticalScrollBar()->maximum());

  chat_scroll_area->verticalScrollBar()->setValue(chat_scroll_area->verticalScrollBar()->maximum());
}

void GuiChatStack::onSendButtonClicked()
{
  emit sendMessage(usr_profile.key_str, message_editor->text_editor->toPlainText());
  message_editor->text_editor->clear();

}

void GuiChatStack::loadHistory(int index)
{
  if(index <= current_active_index)
    {
      QJsonArray history_json_array = data_history_io->readMessage(index);
      for(int i = 0; i < history_json_array.count(); i++)
        {
          QJsonObject history_json_obj = history_json_array[i].toObject();
          chat_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
        }
    }
  else
    {
      qDebug()<<"sth wrong happened!!!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
      return;
    }
}


