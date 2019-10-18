#ifndef GUICENTRALWIDGET_H
#define GUICENTRALWIDGET_H

#include "SideBar.h"
#include "MainBlock.h"

#include <QSystemTrayIcon>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class Window : public QWidget
{
  Q_OBJECT

public:
  explicit Window(QWidget *parent = nullptr);
  ~Window();

  void onMessageReceived(const Message::TextMessage &messageStruct, const bool &fromMe);
  void onCombWidgetClicked(const QString &usrKey);
  void addUsr(UsrData *userData);
  void delUsr(UsrData *userData);
  void changeUsr(UsrData *userData);
  void onUpdateAvailable();

  SideBar *side_bar;
  MainBlock *main_block;

private:
  inline void loadFonts();

  QMenu *tray_icon_menu;
  QAction *hide_action;
  QAction *show_action;
  QAction *quit_action;
  QSystemTrayIcon *tray_icon;
};

#endif // GUICENTRALWIDGET_H
