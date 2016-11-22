#include "ChatStack.h"

ChatScrollWidget::ChatScrollWidget(UsrData *usrData, QWidget *parent) : QWidget(parent)
{
	usr_data = usrData;
	a = 90;
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
  bottom_line->setFixedHeight(2);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setSpacing(5);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->addWidget(top_line);
  main_layout->addLayout(chat_bubble_layout);
  main_layout->addWidget(bottom_line);
	// this is moved from the parent class; layout warning may come from here
//	QVBoxLayout *central_layout = new QVBoxLayout(chat_widget);
//  central_layout->setContentsMargins(0,0,0,0);
//  central_layout->setAlignment(Qt::AlignBottom);
//  central_layout->setMargin(0);
//  central_layout->setSpacing(0);<<

}

ChatScrollWidget::~ChatScrollWidget()
{

}

void ChatScrollWidget::clearChatBubbles()
{
	foreach (TextBubble *temp_chat_bubble_pointer, chat_bubble_list)
    {
      if(temp_chat_bubble_pointer != nullptr)
        {
          temp_chat_bubble_pointer->deleteLater();
        }
      chat_bubble_list.removeOne(temp_chat_bubble_pointer);
		}
}

void ChatScrollWidget::flipUnreadMessage()
{
	qDebug()<<"#ChatScrollWidget::flipUnreadMessage(): Chat stack is loading unread message...";

	if(usr_data->unreadMessageNumber() != 0)
		{
			qDebug()<<"#ChatScrollWidget::flipUnreadMessage(): Chat stack is loading unread message...2";

			QList<QJsonObject> *message_list = usr_data->retrieveUnreadMessage();
			qDebug()<<"#ChatScrollWidget::flipUnreadMessage(): Chat stack is loading unread message...3";

			foreach (QJsonObject history_json_obj, *message_list)
				{
					this->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
					qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
				}
		}

}

void ChatScrollWidget::flipLatestMessage()
{
	qDebug()<<"#ChatScrollWidget::flipLatestMessage(): Chat scroll widget is loading history message...";

	GlobalData::TEST_printUsrProfileStruct(*usr_data->usrProfileStruct(), "tested lastly ");
	QJsonArray *message_json_array = usr_data->flipLatest();
	int message_count = message_json_array->count();
	for(int i = 0; i < message_count; i++)
		{
			QJsonObject history_json_obj = message_json_array->at(i).toObject();
			this->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
			qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
		}
	qDebug()<<" ↳ @GuiChatStack::refreshUI(): Message loaded...";
}

void ChatScrollWidget::flipUpMessage()
{

}

void ChatScrollWidget::flipDownMessage()
{

}

void ChatScrollWidget::addChatBubble(const QString &message, const bool &fromMe)
{
	gui_chat_bubble = new TextBubble(message, !fromMe, this);
  chat_bubble_list.append(gui_chat_bubble);

  chat_bubble_layout->addWidget(gui_chat_bubble);
}





ChatMessageEditor::ChatMessageEditor(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

	text_editor = new TextEdit(this);
  text_editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  text_editor->setFrameStyle(QFrame::NoFrame);
  text_editor->setFont(GlobalData::font_chatTextEditor);
  text_editor->installEventFilter(this);

  ///tools
  expression_label = new LabelButton(this);
  image_label = new LabelButton(this);
  file_label = new LabelButton(this);

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
  ///for test period
    expression_label->setHidden(true);
    image_label->setHidden(true);
    file_label->setHidden(true);

  edit_layout = new QVBoxLayout();
  edit_layout->setAlignment(Qt::AlignLeft);
  edit_layout->setContentsMargins(10,5,15,10);
  edit_layout->setSpacing(5);
  edit_layout->addLayout(tool_layout);
  edit_layout->addWidget(text_editor);

  ///send button
  send_btn = new LabelButton(this);
  send_btn->setDefaultPixmap(":/img/img/send_button_0.png");
  send_btn->setHoveredPixmap(":/img/img/send_button_1.png");
  send_btn->setAlignment(Qt::AlignRight);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setContentsMargins(0,0,20,0);
  main_layout->setSpacing(0);
  main_layout->addLayout(edit_layout);
  main_layout->addWidget(send_btn);


  this->setMaximumHeight(130);
}

ChatMessageEditor::~ChatMessageEditor()
{

}

/// Event filter: capture QEvent outside the class
///   text_editor->installEventFilter(this);
bool ChatMessageEditor::eventFilter(QObject *obj, QEvent *e)
{
  Q_ASSERT(obj == text_editor);
  if(e->type() == QEvent::KeyPress)
    {
      QKeyEvent *event = static_cast<QKeyEvent*>(e);
      if(event->key() == Qt::Key_Return)
        {
          if(event->modifiers() & Qt::ControlModifier)
            {
              control_pressed = true;
              text_editor->insertPlainText("\n");
            }
          else
            {
              control_pressed = false;
              send_btn->setHovered();
            }
          return true;
        }
    }
  if(e->type() == QEvent::KeyRelease)
    {
      QKeyEvent *event = static_cast<QKeyEvent*>(e);
      if (event->key() == Qt::Key_Return)
        {
          if(event->modifiers() & Qt::ControlModifier)
            {
              return true;
            }
          else
            {
              emit sendTriggered();
              send_btn->setDefault();
              return true;
            }
        }
    }

    return false;
}


TextEdit::TextEdit(QWidget *parent)
{
  this->setParent(parent);
}

TextEdit::~TextEdit()
{

}



void TextEdit::dragEnterEvent(QDragEnterEvent *event)
{
  event->accept();
}

void TextEdit::dropEvent(QDropEvent *event)
{
  QList<QUrl> url_list = event->mimeData()->urls();
  if(url_list.isEmpty())
    {
      return;
    }

  if(url_list.count() > 15)
    {
      qDebug()<<"@GuiTextEdit::dropEvent: Too many files dropped";
      return;
    }

  foreach(QUrl url, url_list)
    {
      QString fileName = url.toLocalFile();
      if (fileName.isEmpty())
        {
          break;
        }
      qDebug()<<"@file dropped"<<fileName;
    }

}






ChatStack::ChatStack(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Profile);

  usr_data = new UsrData(this);//empty object
  ///UI
  QFrame *bottom_line = new QFrame(this);
  bottom_line->setFrameShape(QFrame::HLine);
  bottom_line->setFrameShadow(QFrame::Plain);
  bottom_line->setFixedHeight(2);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

//	chat_widget = new ChatScrollWidget(this); <<
  QPalette palette = scroll_area->palette();
  palette.setColor(QPalette::Base, QColor(255,255,255,255));
  scroll_area->setPalette(palette);
  scroll_area->setWidgetResizable(true);
//  scroll_area->setWidget(chat_widget);<<
  scroll_area->setFrameStyle(0);

	message_editor = new ChatMessageEditor(this);

  ///this is a flag to distinguish
  ///////////////////////////////////////Eiffel Tower////////////////////////////////////

  ////main layout

  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(bottom_line);
  main_layout->addWidget(message_editor);

  connect(message_editor, SIGNAL(sendTriggered()), this, SLOT(onSendButtonClicked()));
  connect(message_editor->send_btn, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));

  this->setParent(parent);
}

ChatStack::~ChatStack()
{
	foreach (ChatScrollWidget *widget, chat_scroll_widget_hash.values())
		{
			widget->deleteLater();
		}
}

bool ChatStack::refreshProfile(const QString &usrKey)
{
  if(!this->isDisplaying(usrKey))
    {
      return false;
    }
  else
    {
      this->setIcon(usr_data->avatar());
      this->setTitle(usr_data->name());
      this->setSubTitle(usr_data->ip());
      return true;
    }
}

bool ChatStack::refreshMessage(const QString &usrKey)
{
	if(!isDisplaying(usrKey))
    {
      qDebug()<<"@GuiChatStack::refreshMessage: Message load request denied (different usr)...";
      return false;
    }
  else
    {
      this->flipUnreadMessage();
      return true;
    }
}

void ChatStack::setUsrData(UsrData *usrData)
{
  usr_data = usrData;
}

void ChatStack::display(const QString &usrKey)
{
	/// if usr key is the same, simply ignore
	/// else, test if it exists in scroll_widget_hash
	///		if exits, get one,
	///


	if(!isDisplaying(usrKey))
		{
			qDebug()<<"* | not displaying " << usrKey;
			usr_data = GlobalData::online_usr_data_hash.value(usrKey);
			ChatScrollWidget *temp_chat_scroll_widget;

			//if widget exists
			if(chat_scroll_widget_hash.contains(usrKey))
				{
					qDebug()<<"* | key found in hash, got it";
					temp_chat_scroll_widget = chat_scroll_widget_hash.value(usrKey);
					qDebug()<<temp_chat_scroll_widget->hello();

				}
			else
				{
					qDebug()<<"* | key not found in hash, creating...";
					temp_chat_scroll_widget = new ChatScrollWidget(usr_data, this);
					chat_scroll_widget_hash.insert(usrKey, temp_chat_scroll_widget);
					qDebug()<<temp_chat_scroll_widget->hello();

				}
			qDebug()<<"* | ha?";

			temp_chat_scroll_widget->flipLatestMessage();
			temp_chat_scroll_widget->flipUnreadMessage();

			this->setIcon(usr_data->avatar());
			this->setTitle(usr_data->name());
			this->setSubTitle(usr_data->ip());

			scroll_area->widget()->setHidden(true);
			scroll_area->setWidget(temp_chat_scroll_widget);
		}

	scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());



//  UsrData *temp_usr_data = GlobalData::online_usr_data_map.value(usrKey);

//	//if profile changed
//	if(*usr_data->usrProfileStruct() != *temp_usr_data->usrProfileStruct())
//		{

//			if(!isDisplaying(usrKey))
//        {
//					ChatScrollWidget *temp_chat_scroll_widget;

//					//if chat widget already exist
//					if(!chat_scroll_widget_hash.keys().contains(usrKey))
//						{
//							temp_chat_scroll_widget = new ChatScrollWidget(this);
//							chat_scroll_widget_hash.insert(usr_data->key(), temp_chat_scroll_widget);
//							qDebug()<<"hello1";
//							temp_chat_scroll_widget->adjustSize();
//							qDebug()<<"hello2";
//							//test
//							if(temp_chat_scroll_widget == Q_NULLPTR)
//								{
//									qDebug()<<"!!void ChatStack::flipLatestMessage(): NULL POINTER EXCEPTION!!!!!!!!!";
//								}
//							//$test<<
//						}
//					else
//						{
//							temp_chat_scroll_widget =	chat_scroll_widget_hash.value(usrKey);
//						}
//					scroll_area->widget()->setHidden(true);
//					scroll_area->setWidget(temp_chat_scroll_widget);

//					this->setUsrData(temp_usr_data);
//					this->flipLatestMessage();
//					this->flipUnreadMessage();
//        }

//      this->setIcon(temp_usr_data->avatar());
//      this->setTitle(temp_usr_data->name());
//      this->setSubTitle(temp_usr_data->ip());
//    }

}

bool ChatStack::isDisplaying(const QString &usrKey)
{
  return (usrKey == usr_data->key());
}

void ChatStack::dragEnterEvent(QDragEnterEvent *event)
{
  event->accept();

}

void ChatStack::dropEvent(QDropEvent *event)
{
  qDebug()<<"#GuiChatStack::dropEvent(): file entered.";
  QList<QUrl> urls = event->mimeData()->urls();
  if (urls.isEmpty())
    {
      return;
    }
  QString fileName = urls.first().toLocalFile();
  if (fileName.isEmpty())
    {
      return;
    }
}

void ChatStack::flipUnreadMessage()
{
	ChatScrollWidget *temp_chat_scroll_widget;

	if(chat_scroll_widget_hash.keys().contains(usr_data->key()))
		{
			temp_chat_scroll_widget =	chat_scroll_widget_hash.value(usr_data->key());
		}
	else
		{
			qDebug()<<"!!void ChatStack::flipUnreadMessage(): WIDGET LOST!!!!!!!!!";
		}

  qDebug()<<"@GuiChatStack::flipUnreadMessage(): Chat stack is loading unread message...";
  if(usr_data->unreadMessageNumber() != 0)
    {
      QList<QJsonObject> *message_list = usr_data->retrieveUnreadMessage();
      foreach (QJsonObject history_json_obj, *message_list)
        {
					temp_chat_scroll_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
          qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
        }
    }

#ifdef Q_OS_OSX
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout,
					[this](){
						scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
						timer->deleteLater();
					});
	timer->setSingleShot(true);
	timer->start(100);
#endif
  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);
}

void ChatStack::flipLatestMessage()
{
//  qDebug()<<"@GuiChatStack::flipLatestMessage(): Chat stack is loading history message...";

//	ChatScrollWidget *temp_chat_scroll_widget;

//	if(!chat_scroll_widget_hash.keys().contains(usr_data->key()))
//		{
//			temp_chat_scroll_widget = new ChatScrollWidget(this);
//			chat_scroll_widget_hash.insert(usr_data->key(), temp_chat_scroll_widget);

//			//test
//			if(temp_chat_scroll_widget == Q_NULLPTR)
//				{
//					qDebug()<<"!!void ChatStack::flipLatestMessage(): NULL POINTER EXCEPTION!!!!!!!!!";
//				}
//			//$test
//		}
//	else
//		{
//			temp_chat_scroll_widget =	chat_scroll_widget_hash.value(usr_data->key());
//		}

//  QJsonArray message_json_array = *usr_data->flipLatest();
//  int message_count = message_json_array.count();
//  for(int i = 0; i < message_count; i++)
//    {
//      QJsonObject history_json_obj = message_json_array[i].toObject();

//			temp_chat_scroll_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
//			qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
//    }

//  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
}

void ChatStack::flipUpMessage(const bool &clear)
{
  if(clear)
    {
//      chat_widget->clearChatBubbles();
    }
}

void ChatStack::flipDownMessage(const bool &clear)
{
  if(clear)
    {
//      chat_widget->clearChatBubbles();
    }
}

void ChatStack::onSendButtonClicked()
{
  QString message = message_editor->text_editor->toPlainText();
  if(message.isEmpty())
    {
      scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);
      return;
    }

  emit sendMessage(usr_data->key(), message);
  message_editor->text_editor->clear();

#ifdef Q_OS_OSX
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout,
					[this](){
						scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
						timer->deleteLater();
					});
	timer->setSingleShot(true);
	timer->start(100);
#endif

  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);
}

void ChatStack::onKeyEnterTriggered(bool &pressed)
{
  qDebug()<<"enter key pressed";
  if(pressed)
    {
      message_editor->send_btn->setHovered();
    }
  else
    {
      message_editor->send_btn->setDefault();
      onSendButtonClicked();
    }
}

