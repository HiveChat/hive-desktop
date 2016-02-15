#ifndef GUIMAINBLOCK_H
#define GUIMAINBLOCK_H

#include "GuiChatStack.h"
#include "GuiWelcomeStack.h"
#include "GuiColorPicker.h"
#include "GuiSettingsStack_messaging.h"

#include <QStackedWidget>
#include <QList>
#include <QMap>
#include <QColorDialog>

class GuiMainBlock : public QWidget
{
  Q_OBJECT

public:
  explicit GuiMainBlock(QWidget *parent = 0);
  ~GuiMainBlock();

  GuiChatStack *gui_chat_stack;
  GuiWelcomeStack *gui_welcome_stack;
  GuiSettingsStack_messaging *gui_settings_stack;
  QStackedWidget *main_stacked_widget;

  QMap<QString ,GuiChatStack*> gui_chat_stack_map;

private:
  QVBoxLayout *main_layout;

public slots:
  void displayStaticStack(StaticStackType staticStackType);
  void displayChatStack(QString usrKey);
  void addChatStack(QStringList usrInfoStrList);
  void onMessageRecieved(QStringList message_str_list, bool fromMe);

private slots:
  void onColorDialogTriggered();


signals:
  void whoseMessage(QStringList message_str_list);


};

#endif // GUIMAINBLOCK_H
