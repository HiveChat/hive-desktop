#ifndef GUICENTRALWIDGET_H
#define GUICENTRALWIDGET_H

#include "TabBlock.h"
#include "MainBlock.h"

#include <QSystemTrayIcon>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class GuiCentralWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCentralWidget(QWidget *parent = 0);
  ~GuiCentralWidget();

  GuiTabBlock *gui_tab_block;
  MainBlock *gui_main_block;

private:
  QString usr_key_str;
  QString usr_name_str;
  QString avatar_path_str;

  QStringList my_profile_str_list;

  QHBoxLayout *main_layout;
  QSystemTrayIcon *tray_icon;

  QMenu *tray_icon_menu;
  QAction *hide_action;
  QAction *show_action;
  QAction *quit_action;

  void initAction();
  void initTrayIcon();
  void initTimerTask();

public slots:
  void onMessageReceived(const Message::TextMessageStruct &messageStruct, const bool &fromMe);
  void onCombWidgetClicked(const QString &usrKey);
  void addUsr(UsrData *userData);
  void delUsr(UsrData *userData);
  void changeUsr(UsrData *userData);
  void onUpdateAvailable();

};

#endif // GUICENTRALWIDGET_H
