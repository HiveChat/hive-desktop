#include "Window.h"


Window::Window(QWidget *parent)
  : QWidget(parent)
{    
  loadFonts();

  this->setHidden(true);
  this->setMinimumHeight(600);
  this->setMinimumWidth(900);
  this->setGeometry(this->x(), this->y(), Global::settings.window_width, Global::settings.window_height);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowTitle(QString("Hive! %1.%2.%3 alpha-test")
                       .arg(Global::current_version[0])
                       .arg(Global::current_version[1])
                       .arg(Global::current_version[2]));
#ifndef Q_OS_OSX
  this->setWindowIcon(QIcon(":/img/img/icon.png"));
#endif

  tab_block = new TabBlock(this);
  main_block = new MainBlock(this);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(tab_block);
  main_layout->addWidget(main_block);

  hide_action = new QAction(tr("&Hide"), this);
  show_action = new QAction(tr("&Show"), this);
  quit_action = new QAction(tr("&Quit"), this);

  tray_icon_menu = new QMenu(this);
  tray_icon_menu->addAction(hide_action);
  tray_icon_menu->addAction(show_action);
  tray_icon_menu->addSeparator();
  tray_icon_menu->addAction(quit_action);

  tray_icon = new QSystemTrayIcon(this);
  tray_icon->setIcon(QIcon(":/img/img/tray_0.png"));
  tray_icon->setToolTip("Hive!");
  tray_icon->setContextMenu(tray_icon_menu);
  tray_icon->setVisible(true);
  tray_icon->show();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout,
          [this]() {
            if(Global::settings.window_height != this->height()
               || Global::settings.window_width != this->width())
              {
                Global::settings.window_height = this->height();
                Global::settings.window_width = this->width();

                Global::settings.modified = true;
              }
          });
  timer->setSingleShot(false);
  timer->start(2000);

  connect(tab_block->chat_tab->comb_scroll_widget, &CombScrollWidget::combWidgetClicked,
          this, &Window::onCombWidgetClicked);

  connect(tab_block->home_tab->welcome_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(tab_block->home_tab->list_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(tab_block->home_tab->storage_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(tab_block->settings_tab->messaging_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(tab_block->settings_tab->profile_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(tab_block->settings_tab->questions_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(tab_block->settings_tab->update_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);

  connect(hide_action, &QAction::triggered, this, &QWidget::hide);
  connect(show_action, &QAction::triggered, this, &QWidget::showNormal);
  connect(quit_action, &QAction::triggered, qApp, &QCoreApplication::quit);
  connect(tray_icon, &QSystemTrayIcon::activated, this, &Window::showNormal);
}

Window::~Window()
{
  qDebug()<<"\n@Hive UI is destructed";
}

void Window::loadFonts()
{
#ifdef Q_OS_WIN
      QString font_family = "Verdana";
      GlobalData::font_chatTextEditor = QFont(font_family, 11);
      GlobalData::font_main = QFont(font_family, 6);
      GlobalData::font_chatBubble = GlobalData::font_main;
      GlobalData::font_chatBubble.setPointSize(10);
      GlobalData::font_combWidgetUsrName = GlobalData::font_main;
      GlobalData::font_combWidgetUsrName.setPointSize(10);
      GlobalData::font_combWidgetIpAddr = GlobalData::font_main;
      GlobalData::font_combWidgetIpAddr.setPointSize(7);
      GlobalData::font_menuButton = GlobalData::font_main;
      GlobalData::font_menuButton.setPointSize(10);
      GlobalData::font_scrollStackTitle = GlobalData::font_main;
      GlobalData::font_scrollStackTitle.setPointSize(10);
      GlobalData::font_scrollStackSubtitle = GlobalData::font_main;
      GlobalData::font_scrollStackSubtitle.setPointSize(9);
#endif //Q_OS_WIN


#ifndef Q_OS_WIN ///windows can't load font from qrc, don't know why.
    int fontId;
    QString fontFamily;

    fontId = QFontDatabase::addApplicationFont(":/font/font/GillSans.ttc");
    if(fontId == -1)
      {
        return;
      }

    fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    Global::font_chatTextEditor = QFont(fontFamily, 16);
    if(fontId == -1)
      {
        return;
      }

    fontId = QFontDatabase::addApplicationFont(":/font/font/Futura.ttc");
    fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    Global::font_main = QFont(fontFamily);
    Global::font_chatBubble = Global::font_main;
    Global::font_chatBubble.setPointSize(14);
    Global::font_combWidgetUsrName = Global::font_main;
    Global::font_combWidgetUsrName.setPointSize(15);
    Global::font_combWidgetIpAddr = Global::font_main;
    Global::font_combWidgetIpAddr.setPointSize(11);
    Global::font_menuButton = Global::font_main;
    Global::font_menuButton.setPointSize(14);
    Global::font_scrollStackTitle = Global::font_main;
    Global::font_scrollStackTitle.setPointSize(15);
    Global::font_scrollStackSubtitle = Global::font_main;
    Global::font_scrollStackSubtitle.setPointSize(13);

#endif //Q_OS_WIN

}

void Window::onMessageReceived(const Message::TextMessage &messageStruct, const bool &fromMe)
{
  if(fromMe)
    {
      main_block->chat_stack->refreshMessage(messageStruct.reciever);
    }
  else
    {
      //if not displaying the usr
      if(!main_block->chat_stack->refreshMessage(messageStruct.sender))
        {
          UsrData *temp_usr_data = AppDataManager::usr_data_hash.value(messageStruct.sender);
          tab_block->chat_tab->comb_scroll_widget->refreshBadgeNumber(messageStruct.sender, temp_usr_data->getUnreadMessageNumber());
          if(Global::settings.notification.message_notification
             && Global::settings.update.auto_check_update)
            {
              if(Global::settings.notification.message_detail_notification)
                {
                  tray_icon->showMessage(temp_usr_data->getName(), messageStruct.message);
                }
              else
                {
                  tray_icon->showMessage(temp_usr_data->getName(), "new message");
                }
            }
        }
    }
}

void Window::onCombWidgetClicked(const QString &usrKey)
{
  main_block->displayChatStack(usrKey);
  tab_block->chat_tab->comb_scroll_widget->refreshBadgeNumber(usrKey, 0);
}

void Window::addUsr(UsrData *userData)
{
  if(tab_block->chat_tab->comb_scroll_widget->contains(userData->getKey()))
    {
      qDebug()<<"#GuiCentralWidget::addUsr(): Already exists.";
      return;
    }
  tab_block->chat_tab->comb_scroll_widget->addComb(userData->getUsrProfile());
  main_block->home_stack_list->addUsr(userData->getUsrProfile());
}

void Window::delUsr(UsrData *userData)
{
  (void)userData;
}

void Window::changeUsr(UsrData *userData)
{
  qDebug()<<"Update user info";
  tab_block->chat_tab->comb_scroll_widget->refreshComb(userData->getUsrProfile());
  main_block->chat_stack->refreshProfile(userData->getKey());
  main_block->home_stack_list->refreshUsrProfile(userData->getUsrProfile());
}

void Window::onUpdateAvailable()
{
  if(Global::settings.notification.update_notification
     && Global::settings.update.auto_check_update)
    {
      QString message = QString("current version: %0.%1.%2\nnew version: %3.%4.%5")
          .arg(Global::current_version[0])
          .arg(Global::current_version[1])
          .arg(Global::current_version[2])
          .arg(Global::update_struct.version[0])
          .arg(Global::update_struct.version[1])
          .arg(Global::update_struct.version[2]);
      tray_icon->showMessage("Update Available", message);
    }
}



