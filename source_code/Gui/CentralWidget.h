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
  QMenu *tray_icon_menu;
  QAction *hide_action;
  QAction *show_action;
  QAction *quit_action;
  QSystemTrayIcon *tray_icon;

public slots:
  void onMessageReceived(const Message::TextMessageStruct &messageStruct, const bool &fromMe);
  void onCombWidgetClicked(const QString &usrKey);
  void addUsr(UsrData *userData);
  void delUsr(UsrData *userData);
  void changeUsr(UsrData *userData);
  void onUpdateAvailable();

};

#endif // GUICENTRALWIDGET_H
