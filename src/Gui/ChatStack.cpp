#include "ChatStack.h"

//////////////////////////mid////////////////////////////////

MessageViewer::MessageViewer(QWidget *parent) : QWidget(parent)
{
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::transparent);
  this->setAutoFillBackground(true);
  this->setPalette(palette);

  chat_bubble_layout = new QVBoxLayout();
  chat_bubble_layout->setAlignment(Qt::AlignTop);
  chat_bubble_layout->addStretch();
  chat_bubble_layout->setContentsMargins(5,30,5,30);

  ///lines
  QFrame *topLine = new QFrame(this);
  topLine->setFrameShape(QFrame::HLine);
  topLine->setFrameShadow(QFrame::Plain);
  topLine->setFixedHeight(2);
  topLine->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  QFrame *bottomLine = new QFrame(this);
  bottomLine->setFrameShape(QFrame::HLine);
  bottomLine->setFrameShadow(QFrame::Plain);
  bottomLine->setFixedHeight(2);
  bottomLine->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setSpacing(5);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->addWidget(topLine);
  main_layout->addLayout(chat_bubble_layout);
  main_layout->addWidget(bottomLine);

}

MessageViewer::~MessageViewer()
{

}

void MessageViewer::clear()
{
  for (TextBubble *b : chat_bubble_list)
    {
      if(b != nullptr)
        {
          b->deleteLater();
        }
      chat_bubble_list.removeOne(b);
    }
}

void MessageViewer::addChatBubble(const QString &message, const bool &fromMe)
{
  TextBubble *b = new TextBubble(message, !fromMe, this);
  chat_bubble_list.append(b);
  chat_bubble_layout->addWidget(b);
  chat_bubble_layout->setAlignment(b, fromMe ? Qt::AlignRight : Qt::AlignLeft);

}



MessageEditor::MessageEditor(QWidget *parent)
  : QWidget(parent)
{
//  this->setStyleSheet("MessageEditor { border-radius: 16px; "
//                      "background-color: #ffffff; "
//                      "margin-left: 100px;"
//                      "margin-right: 10px;"
//                      "padding-left: 10px;"
//                      "padding-right: 10px;"
//                      "outline: none; }");

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

MessageEditor::~MessageEditor()
{

}

/// Event filter: capture QEvent outside the class
///   text_editor->installEventFilter(this);
bool MessageEditor::eventFilter(QObject *obj, QEvent *e)
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
  : QTextEdit(parent)
{
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
  QList<QUrl> urlList = event->mimeData()->urls();
  if(urlList.isEmpty())
    {
      return;
    }

  if(urlList.count() > 15)
    {
      qDebug()<<"@GuiTextEdit::dropEvent: Too many files dropped";
      return;
    }

  for(QUrl url : urlList)
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
  : ScrollStack(LayoutStyle::Profile, parent)
  , chat_widget(new MessageViewer(this))
  , user(new UsrData())
{
  QPixmap bkgImg(":/img/img/chat_bkg_honey.png");
  bkgImg.setDevicePixelRatio(2.0);
  QPalette palette = scroll_area->palette();
  palette.setColor(QPalette::Base, QColor(255,255,255,255));
//  palette.setBrush(QPalette::Background, bkgImg);
  scroll_area->setPalette(palette);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(chat_widget);
  scroll_area->setFrameStyle(0);

  message_editor = new MessageEditor(this);

  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
  main_layout->addWidget(message_editor);

  connect(message_editor, &MessageEditor::sendTriggered,
          this, &ChatStack::onSendButtonClicked);
  connect(message_editor->send_btn, &LabelButton::clicked,
          this, &ChatStack::onSendButtonClicked);
}

ChatStack::~ChatStack()
{
}

void ChatStack::refreshProfile()
{
  this->setIcon(user->getAvatar());
  this->setTitle(user->getName());
  this->setSubTitle(user->getIp());
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

void ChatStack::setUsr(UsrData *usrData)
{
  user = usrData;
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
  UsrData *incomingUsr;
  if(AppDataManager::usr_data_hash.contains(usrKey))
    incomingUsr = AppDataManager::usr_data_hash.value(usrKey);
  else
    incomingUsr = AppDataManager::usr_data_hash.value(usrKey);

  if(*user->getProfile() != *incomingUsr->getProfile())
    {
      saveEditingMessage();
      setUsr(incomingUsr);
      loadEditingMessage();
      loadMessageViewer();
      refreshProfile();
    }
}

bool ChatStack::isDisplaying(const QString &usrKey)
{
  return user->getKey() == usrKey;
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
      return;
  QString fileName = urls.first().toLocalFile();
  if (fileName.isEmpty())
    return;
}

void ChatStack::saveEditingMessage()
{
  if(editing_message_hash.contains(user->getKey()))
      editing_message_hash.take(user->getKey());
  editing_message_hash.insert(user->getKey(), message_editor->text_editor->toPlainText());
}

void ChatStack::loadEditingMessage()
{
  if(editing_message_hash.contains(user->getKey()))
    message_editor->text_editor->setText(editing_message_hash.value(user->getKey()));
  else
    message_editor->text_editor->clear();
}

void ChatStack::loadMessageViewer()
{
  if(message_viewer_hash.contains(user->getKey()))
    {
       MessageViewer *widget = message_viewer_hash.value(user->getKey());
       chat_widget = widget;
    }
  else
    {
      MessageViewer *widget = new MessageViewer(this);
      chat_widget = widget;
      message_viewer_hash.insert(user->getKey(), widget);
      this->flipLatestMessage(false);
    }

  this->flipUnreadMessage();
  scroll_area->takeWidget();
  scroll_area->setWidget(chat_widget);
}

void ChatStack::flipUnreadMessage()
{
  Log::gui(Log::Info, "GuiChatStack::flipUnreadMessage()", "chat stack is loading unread message...");
  if(user->getUnreadMessageNumber() != 0)
    {
      for(QJsonObject history : *user->retrieveUnreadMessage())
        {
          chat_widget->addChatBubble(history["message"].toString(), history["fromMe"].toBool());
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
      chat_widget->clear();
    }

  Log::gui(Log::Info, "GuiChatStack::flipLatestMessage()", "chat stack is loading latest history message...");
  QJsonArray messages = *user->flipLatest();
  for(int i = 0; i < messages.count(); ++ i)
    {
      QJsonObject history = messages[i].toObject();

      chat_widget->addChatBubble(history["message"].toString(), history["fromMe"].toBool());
      qDebug()<<" | GuiChatStack::refreshUI(): Message loaded...";
    }

  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
}

void ChatStack::flipUpMessage(const bool &clear)
{
  if(clear)
    chat_widget->clear();
}

void ChatStack::flipDownMessage(const bool &clear)
{
  if(clear)
    chat_widget->clear();
}

void ChatStack::onSendButtonClicked()
{
  if(key_lock || easter_animating)
    return;
  key_lock = true;

  if(!user->isOnline())
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

      Log::gui(Log::Info, "GuiChatStack::onSendButtonClicked()", "user \"" + user->getName() +"\" not online");

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

  emit sendMessage(user->getKey(), message);
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
    return;

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

