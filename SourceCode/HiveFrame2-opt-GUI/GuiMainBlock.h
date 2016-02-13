#ifndef GUIMAINBLOCK_H
#define GUIMAINBLOCK_H

#include "GuiChatStack.h"
#include "GuiScrollStack.h"
#include "GuiWelcomeStack.h"

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
  GuiScrollStack *gui_settings_stack;
  QStackedWidget *main_stacked_widget;

  QMap<QString ,GuiChatStack*> gui_chat_stack_map;

private:
  QVBoxLayout *main_layout;
  QPalette text_palette;

  void setSettings_profile();
  void setSettings_messaging();

  void setHome_storage();

public slots:
  void displayChatStack(QString usrKey);
  void displayWelcomeStack();
  void addChatStack(QStringList usrInfoStrList);
  void onMessageRecieved(QStringList message_str_list, bool fromMe);

signals:
  void whoseMessage(QStringList message_str_list);


};

#endif // GUIMAINBLOCK_H
