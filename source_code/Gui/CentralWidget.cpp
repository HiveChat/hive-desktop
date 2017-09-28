#include "CentralWidget.h"


CentralWidget::CentralWidget(QWidget *parent)
  : QWidget(parent)
  , gui_tab_block(new GuiTabBlock(this))
  , gui_main_block(new MainBlock(this))
  , hide_action(new QAction(tr("&Hide"), this))
  , show_action(new QAction(tr("&Show"), this))
  , quit_action(new QAction(tr("&Quit"), this))
  , tray_icon_menu(new QMenu(this))
  , tray_icon(new QSystemTrayIcon(this))
{    
  this->setMinimumHeight(600);
  this->setMinimumWidth(900);
  this->setGeometry(this->x(), this->y(), GlobalData::settings_struct.window_width, GlobalData::settings_struct.window_height);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowTitle(QString("Hive! %1.%2.%3 alpha-test")
                       .arg(GlobalData::current_version[0])
                       .arg(GlobalData::current_version[1])
                       .arg(GlobalData::current_version[2]));
#ifndef Q_OS_OSX
  this->setWindowIcon(QIcon(":/img/img/icon.png"));
#endif

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(gui_tab_block);
  main_layout->addWidget(gui_main_block);

  tray_icon_menu->addAction(hide_action);
  tray_icon_menu->addAction(show_action);
  tray_icon_menu->addSeparator();
  tray_icon_menu->addAction(quit_action);

  tray_icon->setIcon(QIcon(":/img/img/tray_0.png"));
  tray_icon->setToolTip("Hive!");
  tray_icon->setContextMenu(tray_icon_menu);
  tray_icon->setVisible(true);
  tray_icon->show();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout,
          [this]() {
            if(GlobalData::settings_struct.window_height != this->height()
               || GlobalData::settings_struct.window_width != this->width())
              {
                GlobalData::settings_struct.window_height = this->height();
                GlobalData::settings_struct.window_width = this->width();

                GlobalData::settings_struct.modified_lock = true;
              }
          });
  timer->setSingleShot(false);
  timer->start(2000);

  connect(gui_tab_block->chat_tab->comb_scroll_widget, &ChatTab_comb_scroll_widget::combWidgetClicked,
          this, &CentralWidget::onCombWidgetClicked);

  connect(gui_tab_block->home_tab->welcome_btn, &MenuButton::clicked, 
          gui_main_block, &MainBlock::displayStaticStack);
  connect(gui_tab_block->home_tab->list_btn, &MenuButton::clicked, 
          gui_main_block, &MainBlock::displayStaticStack);
  connect(gui_tab_block->home_tab->storage_btn, &MenuButton::clicked, 
          gui_main_block, &MainBlock::displayStaticStack);

  connect(gui_tab_block->settings_tab->messaging_btn, &MenuButton::clicked, 
          gui_main_block, &MainBlock::displayStaticStack);
  connect(gui_tab_block->settings_tab->profile_btn, &MenuButton::clicked, 
          gui_main_block, &MainBlock::displayStaticStack);
  connect(gui_tab_block->settings_tab->questions_btn, &MenuButton::clicked, 
          gui_main_block, &MainBlock::displayStaticStack);
  connect(gui_tab_block->settings_tab->update_btn, &MenuButton::clicked, 
          gui_main_block, &MainBlock::displayStaticStack);

  connect(hide_action, &QAction::triggered, this, &QWidget::hide);
  connect(show_action, &QAction::triggered, this, &QWidget::showNormal);
  connect(quit_action, &QAction::triggered, qApp, &QCoreApplication::quit);
  connect(tray_icon, &QSystemTrayIcon::activated, this, &CentralWidget::showNormal);

  foreach(UsrData *usrData, GlobalData::offline_usr_data_hash.values())
    {
      this->addUsr(usrData);
    }
}

CentralWidget::~CentralWidget()
{
  qDebug()<<"\n@Hive UI is destructed";
}

void CentralWidget::onMessageReceived(const Message::TextMessageStruct &messageStruct, const bool &fromMe)
{
  if(fromMe)
    {
      gui_main_block->gui_chat_stack->refreshMessage(messageStruct.reciever);
    }
  else
    {
      //if not displaying the usr
      if(!gui_main_block->gui_chat_stack->refreshMessage(messageStruct.sender))
        {
          UsrData *temp_usr_data = GlobalData::online_usr_data_hash.value(messageStruct.sender);
          gui_tab_block->chat_tab->comb_scroll_widget->refreshBadgeNumber(messageStruct.sender, temp_usr_data->getUnreadMessageNumber());
          if(GlobalData::settings_struct.notification.message_notification
             && GlobalData::settings_struct.update.auto_check_update)
            {
              if(GlobalData::settings_struct.notification.message_detail_notification)
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

void CentralWidget::onCombWidgetClicked(const QString &usrKey)
{
  gui_main_block->displayChatStack(usrKey);
  gui_tab_block->chat_tab->comb_scroll_widget->refreshBadgeNumber(usrKey, 0);
}

void CentralWidget::addUsr(UsrData *userData)
{
  if(gui_tab_block->chat_tab->comb_scroll_widget->contains(userData->getKey()))
    {
      qDebug()<<"#GuiCentralWidget::addUsr(): Already exists.";
      return;
    }
  gui_tab_block->chat_tab->comb_scroll_widget->addComb(userData->getUsrProfileStruct());
  gui_main_block->gui_home_stack_list->addUsr(userData->getUsrProfileStruct());
}

void CentralWidget::delUsr(UsrData *userData)
{
  userData;
}

void CentralWidget::changeUsr(UsrData *userData)
{
  qDebug()<<"updated GUI";
  gui_tab_block->chat_tab->comb_scroll_widget->refreshComb(userData->getUsrProfileStruct());
  gui_main_block->gui_chat_stack->refreshProfile(userData->getKey());
  gui_main_block->gui_home_stack_list->refreshUsrProfile(userData->getUsrProfileStruct());
}

void CentralWidget::onUpdateAvailable()
{
  if(GlobalData::settings_struct.notification.update_notification
     && GlobalData::settings_struct.update.auto_check_update)
    {
      QString message = QString("current version: %0.%1.%2\nnew version: %3.%4.%5")
          .arg(GlobalData::current_version[0])
          .arg(GlobalData::current_version[1])
          .arg(GlobalData::current_version[2])
          .arg(GlobalData::update_struct.version[0])
          .arg(GlobalData::update_struct.version[1])
          .arg(GlobalData::update_struct.version[2]);
      tray_icon->showMessage("Update Available", message);
    }
}



