#ifndef GUIMAINBLOCK_H
#define GUIMAINBLOCK_H

#include "GuiChatStack.h"
#include "GuiColorPicker.h"

#include "GuiWelcomeStack.h"
#include "GuiHomeStack_storage.h"
#include "GuiSettingsStack_messaging.h"
#include "GuiSettingsStack_profile.h"
#include "GuiSettingsStack_questions.h"

#include <QStackedWidget>
#include <QList>
#include <QMap>

class GuiMainBlock : public QWidget
{
  Q_OBJECT

public:
  explicit GuiMainBlock(QWidget *parent = 0);
  ~GuiMainBlock();

  GuiChatStack *gui_chat_stack;
  QStackedWidget *main_stacked_widget;

  QMap<QString ,GuiChatStack*> gui_chat_stack_map;

private:
  QWidget *static_stack_widget = NULL;
  StaticStackType current_static_stack = NULL_Stack;
  QVBoxLayout *main_layout;

public slots:
  void displayStaticStack(StaticStackType staticStackType);
  void displayChatStack(QString usrKey);
  GuiChatStack *addChatStack(UsrProfileStruct *usrProfileStruct);
  void onMessageRecieved(QStringList message_str_list, bool fromMe);

private slots:
  void onColorDialogTriggered();


signals:
  void whoseMessage(QStringList message_str_list);


};

#endif // GUIMAINBLOCK_H
