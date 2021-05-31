#include "Window.h"


Window::Window(QWidget *parent)
  : QWidget(parent)
{
  this->setHidden(true);
  this->setMinimumHeight(600);
  this->setMinimumWidth(900);
  this->setGeometry(this->x(), this->y(), Global::settings.window_width, Global::settings.window_height);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowTitle(QString("Hive!"));
#ifndef Q_OS_OSX
  this->setWindowIcon(QIcon(":/img/img/icon.png"));
#endif

  side_bar = new SideBar(this);
  main_block = new MainBlock(this);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
  main_layout->addWidget(side_bar);
  main_layout->addWidget(main_block);

  hide_action = new QAction(tr("&Hide"), this);
  show_action = new QAction(tr("&Show"), this);
  quit_action = new QAction(tr("&Quit"), this);

  tray_icon_menu = new QMenu(this);
  tray_icon_menu->addAction(hide_action);
  tray_icon_menu->addAction(show_action);
  tray_icon_menu->addSeparator();
  tray_icon_menu->addAction(quit_action);

  QIcon icon(":/img/img/tray_0.png");
  icon.setIsMask(true);
  tray_icon = new QSystemTrayIcon(this);
  tray_icon->setIcon(icon);
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

  connect(side_bar->contacts_tab->contact_scroll_widget, &ContactsScrollWidget::contactWidgetClicked,
          this, &Window::onCombWidgetClicked);

  connect(side_bar->home_tab->welcome_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(side_bar->home_tab->list_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(side_bar->home_tab->storage_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(side_bar->settings_tab->messaging_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(side_bar->settings_tab->profile_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(side_bar->settings_tab->questions_btn, &MenuButton::clicked,
          main_block, &MainBlock::displayStaticStack);
  connect(side_bar->settings_tab->update_btn, &MenuButton::clicked,
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
          side_bar->contacts_tab->contact_scroll_widget->refreshBadgeNumber(messageStruct.sender, temp_usr_data->getUnreadMessageNumber());
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
  side_bar->contacts_tab->contact_scroll_widget->refreshBadgeNumber(usrKey, 0);
}

void Window::addUsr(UsrData *userData)
{
  if(side_bar->contacts_tab->contact_scroll_widget->contains(userData->getKey()))
    {
      qDebug()<<"#GuiCentralWidget::addUsr(): Already exists.";
      return;
    }
  side_bar->contacts_tab->contact_scroll_widget->addComb(userData->getProfile());
  main_block->home_stack_list->addUsr(userData->getProfile());
}

void Window::delUsr(UsrData *userData)
{
  (void)userData;
}

void Window::changeUsr(UsrData *userData)
{
  qDebug()<<"Update user info";
  side_bar->contacts_tab->contact_scroll_widget->refreshComb(userData->getProfile());
  if(main_block->chat_stack->isDisplaying(userData->getKey()))
    main_block->chat_stack->refreshProfile();
  main_block->home_stack_list->refreshUser(userData->getProfile());
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



