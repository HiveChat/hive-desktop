#include "ChatStack.h"

//////////////////////////mid////////////////////////////////

ChatStack_chat_widget::ChatStack_chat_widget(QWidget *parent) : QWidget(parent)
{
  //test

  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::white);
  this->setAutoFillBackground(true);
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

}

ChatStack_chat_widget::~ChatStack_chat_widget()
{

}

void ChatStack_chat_widget::clearChatBubbles()
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

void ChatStack_chat_widget::addChatBubble(const QString &message, const bool &fromMe)
{
  chat_bubble = new TextBubble(message, !fromMe, this);
  chat_bubble_list.append(chat_bubble);

  chat_bubble_layout->addWidget(chat_bubble);
}

//////////////////////////bottom//////////////////////////////////////

ChatStack_message_editor::ChatStack_message_editor(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  text_editor = new TextEdit(this);
  text_editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  text_editor->setFrameStyle(QFrame::NoFrame);
  text_editor->setFont(Global::font_chatTextEditor);
  text_editor->installEventFilter(this);

  ///tools
  expression_label = new LabelButton(70, this);
  expression_label->setDefaultPixmap(":/img/img/expression_label_0.png");
  expression_label->setHoveredPixmap(":/img/img/expression_label_1.png");

  image_label = new LabelButton(70, this);
  image_label->setDefaultPixmap(":/img/img/image_label_0.png");
  image_label->setHoveredPixmap(":/img/img/image_label_1.png");

  file_label = new LabelButton(70, this);
  file_label->setDefaultPixmap(":/img/img/file_label_0.png");
  file_label->setHoveredPixmap(":/img/img/file_label_1.png");

  file_progress_bar = new QProgressBar(this);
  file_progress_bar->setMaximumWidth(300);
  file_progress_bar->setHidden(true);

  file_progress_label = new QLabel("376.7M / 0.5G | 1.2M/s", this);
  file_progress_label->setHidden(true);

  file_tran_ani = new QVariantAnimation(this);

  tool_layout = new QHBoxLayout();
  tool_layout->setAlignment(Qt::AlignLeft);
  tool_layout->setContentsMargins(0,5,5,5);
  tool_layout->setSpacing(15);
  tool_layout->addWidget(expression_label);
  tool_layout->addWidget(image_label);
  tool_layout->addWidget(file_label);
  tool_layout->addSpacing(30);
  tool_layout->addWidget(file_progress_bar, 0, Qt::AlignLeft);
  tool_layout->addWidget(file_progress_label, 0, Qt::AlignLeft);
  ///for test period
//    expression_label->setHidden(true);
//    image_label->setHidden(true);
//    file_label->setHidden(true);

  edit_layout = new QVBoxLayout();
  edit_layout->setAlignment(Qt::AlignLeft);
  edit_layout->setContentsMargins(10,5,15,10);
  edit_layout->setSpacing(5);
  edit_layout->addLayout(tool_layout);
  edit_layout->addWidget(text_editor);

  ///send button
  send_btn = new LabelButton(0, this);
  send_btn->setDefaultPixmap(":/img/img/send_button_0.png");
  send_btn->setHoveredPixmap(":/img/img/send_button_1.png");
  send_btn->setAlignment(Qt::AlignRight);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setContentsMargins(0,0,20,0);
  main_layout->setSpacing(0);
  main_layout->addLayout(edit_layout);
  main_layout->addWidget(send_btn);

  connect(file_label, &LabelButton::clicked,
          [this]() {
            QString directory =
            QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files")
                                     , QStandardPaths::writableLocation(QStandardPaths::HomeLocation)));
          }

          );


  connect(file_label, &LabelButton::entered,
          [this]() {
            file_tran_ani = new QVariantAnimation(this);
            file_tran_ani->setStartValue(0);
            file_tran_ani->setEndValue(75);
            file_tran_ani->setDuration(500);
            file_tran_ani->setEasingCurve(QEasingCurve::OutCirc);
            connect(file_tran_ani, &QVariantAnimation::valueChanged,
                    [this](QVariant value) {
                      file_progress_bar->setValue(value.toInt()); //<<
                    });
            connect(file_tran_ani, &QVariantAnimation::finished,
                    [this]() {
                      file_label_hovered = true;
                    });
            file_progress_label->setHidden(false);
            file_progress_bar->setHidden(false);
            file_tran_ani->start();
          });

  connect(file_label, &LabelButton::left,
          [this]() {
            file_label_hovered = true;
            file_progress_label->setHidden(true);
            file_progress_bar->setHidden(true);
            file_progress_bar->setValue(0);

            if(file_tran_ani != Q_NULLPTR)
              {
                file_tran_ani->stop();
                file_tran_ani->deleteLater();
                file_tran_ani = Q_NULLPTR;
              }
          });


  this->setMaximumHeight(130);
}

ChatStack_message_editor::~ChatStack_message_editor()
{

}

/// Event filter: capture QEvent outside the class
///   text_editor->installEventFilter(this);
bool ChatStack_message_editor::eventFilter(QObject *obj, QEvent *e)
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

  usr_data = new UsrData();//empty object
  ///UI
  QFrame *bottom_line = new QFrame(this);
  bottom_line->setFrameShape(QFrame::HLine);
  bottom_line->setFrameShadow(QFrame::Plain);
  bottom_line->setFixedHeight(2);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  chat_widget = new ChatStack_chat_widget(this);
  QPalette palette = scroll_area->palette();
  palette.setColor(QPalette::Base, QColor(255,255,255,255));
  scroll_area->setPalette(palette);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(chat_widget);
  scroll_area->setFrameStyle(0);

  message_editor = new ChatStack_message_editor(this);

  ////main layout
//  QVBoxLayout *central_layout = new QVBoxLayout(chat_widget);
//  central_layout->setContentsMargins(0,0,0,0);
//  central_layout->setAlignment(Qt::AlignBottom);
//  central_layout->setMargin(0);
//  central_layout->setSpacing(0);

  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(bottom_line);
  main_layout->addWidget(message_editor);

  connect(message_editor, &ChatStack_message_editor::sendTriggered,
          this, &ChatStack::onSendButtonClicked);
  connect(message_editor->send_btn, &LabelButton::clicked,
          this, &ChatStack::onSendButtonClicked);
//  connect(scroll_area->verticalScrollBar(), &QScrollBar::sliderReleased,
//          [this](){
//            Log::gui(Log::Normal, "hello()", "hello");
//          });

  this->setParent(parent);
}

ChatStack::~ChatStack()
{
  //  this->set
}

bool ChatStack::refreshProfile(const QString &usrKey)
{
  if(!this->isDisplaying(usrKey))
    {
      return false;
    }
  else
    {
      this->setIcon(usr_data->getAvatar());
      this->setTitle(usr_data->getName());
      this->setSubTitle(usr_data->getIp());
      return true;
    }
}

bool ChatStack::refreshMessage(const QString &usrKey)
{
  if(!this->isDisplaying(usrKey))
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

void ChatStack::updateFileTranProgress()
{
//  if(GlobalData::file_tran_progress_hash.contains(usr_data->key()))
//  {
//    if(!GlobalData::file_tran_progress_hash.value(usr_data->key()).isEmpty())
//      {
//        foreach (QPair<int, int> progress_pair, GlobalData::file_tran_progress_hash.value(usr_data->key()))
//          {
//            file_tran_progress_pair.first += progress_pair.first;
//            file_tran_progress_pair.second += progress_pair.second;///////////< not applicable!!!!!!!!!!

//          }
//      }
//  }
}

void ChatStack::display(const QString &usrKey)
{
  UsrData *temp_usr_data;
  if(AppDataManager::usr_data_hash.contains(usrKey))
    {
      temp_usr_data = AppDataManager::usr_data_hash.value(usrKey);
    }
  else
    {
      temp_usr_data = AppDataManager::usr_data_hash.value(usrKey);
    }

  // if different usr or updated usr is refreshing
  if(*usr_data->getUsrProfile() != *temp_usr_data->getUsrProfile())
    {
      if(usr_data->getKey() != temp_usr_data->getKey())
        {
          // can you read this?
          if(editing_message_hash.contains(usr_data->getKey()))
            {
              editing_message_hash.take(usr_data->getKey());
            }
          editing_message_hash.insert(usr_data->getKey(), message_editor->text_editor->toPlainText());


          this->setUsrData(temp_usr_data);


          if(editing_message_hash.contains(usrKey))
            {
              message_editor->text_editor->setText(editing_message_hash.value(usrKey));
            }
          else
            {
              message_editor->text_editor->clear();
              editing_message_hash.insert(usrKey, "");
            }


          if(chat_widget_hash.contains(usrKey))
            {
               ChatStack_chat_widget *widget = chat_widget_hash.value(usrKey);
               chat_widget = widget;
            }
          else
            {
              ChatStack_chat_widget *widget = new ChatStack_chat_widget(this);
              chat_widget = widget;
              chat_widget_hash.insert(usrKey, widget);
              this->flipLatestMessage(false);
            }


          this->flipUnreadMessage();
          scroll_area->takeWidget();
          scroll_area->setWidget(chat_widget);
        }


      this->refreshProfile(usrKey);

    }
}

bool ChatStack::isDisplaying(const QString &usrKey)
{
  return (usrKey == usr_data->getKey());
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
  Log::gui(Log::Info, "GuiChatStack::flipUnreadMessage()", "chat stack is loading unread message...");
  if(usr_data->getUnreadMessageNumber() != 0)
    {
      QList<QJsonObject> *message_list = usr_data->retrieveUnreadMessage();
      foreach (QJsonObject history_json_obj, *message_list)
        {
          chat_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
          qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
        }
    }

#ifdef Q_OS_OSX
  QTimer::singleShot(50, [this](){
      scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
    });
#endif

  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);
}

void ChatStack::flipLatestMessage(const bool &clear)
{
  if(clear)
    {
      chat_widget->clearChatBubbles();
    }

  Log::gui(Log::Info, "GuiChatStack::flipLatestMessage()", "chat stack is loading latest history message...");
  QJsonArray message_json_array = *usr_data->flipLatest();
  int message_count = message_json_array.count();
  for(int i = 0; i < message_count; i++)
    {
      QJsonObject history_json_obj = message_json_array[i].toObject();

      chat_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
      qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
    }

  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
}

void ChatStack::flipUpMessage(const bool &clear)
{
  if(clear)
    {
      chat_widget->clearChatBubbles();
    }
}

void ChatStack::flipDownMessage(const bool &clear)
{
  if(clear)
    {
      chat_widget->clearChatBubbles();
    }
}

void ChatStack::onSendButtonClicked()
{
  if(key_lock)
    {
      return;
    }
  if(easter_animating)
    {
      return;
    }

  key_lock = true;


  if(!usr_data->isOnline())
    {
      if(click_num == 0)
        {
          first_click_time = QTime::currentTime();
          click_num ++;
        }
      else if(click_num == 30)
        {
          if(first_click_time.addSecs(6) >= QTime::currentTime())
            {
              qDebug()<<click_num;
              easter_animating = true;
              message_editor->send_btn->setHovered();
              message_editor->send_btn->setDisabled(true);
              QVariantAnimation *animation = new QVariantAnimation(this);
              animation->setStartValue(0);
              animation->setEndValue(50);
              animation->setDuration(3000);
              animation->setEasingCurve(QEasingCurve::OutCirc);
              connect(animation, &QVariantAnimation::valueChanged,
                      [this](QVariant value) {
                        message_editor->send_btn->setGeometry(message_editor->send_btn->x(),
                                                              message_editor->send_btn->y() + value.toInt(),
                                                              message_editor->send_btn->width(),
                                                              message_editor->send_btn->height());
                      });
              connect(animation, &QVariantAnimation::finished,
                      [this]{
                        message_editor->send_btn->setHidden(true);
                      });
              animation->start();
              click_num ++;
            }
          else
            {
              click_num = 0;
            }
        }
      else if(click_num < 30)
        {
          click_num ++;
        }

      Log::gui(Log::Info, "GuiChatStack::onSendButtonClicked()", "user \"" + usr_data->getName() +"\" not online");

      key_lock = false;
      return;
    }

  QString message = message_editor->text_editor->toPlainText();
  if(message.isEmpty())
    {
      scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);

      key_lock = false;
      return;
    }

  emit sendMessage(usr_data->getKey(), message);
  message_editor->text_editor->clear();

#ifdef Q_OS_OSX
  QTimer::singleShot(100, [this](){
      scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
    });
#endif

  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);

  key_lock = false;
}

void ChatStack::onKeyEnterTriggered(bool &pressed)
{
  if(easter_animating)
    {
      return;
    }

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

