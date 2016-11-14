#ifndef GUIMAINBLOCK_H
#define GUIMAINBLOCK_H

#include "ChatStack.h"
#include "Gui/Frameworks/Widgets/ColorPicker.h"

#include "HomeStack_welcome.h"
#include "HomeStack_list.h"
#include "HomeStack_storage.h"
#include "SettingsStack_messaging.h"
#include "SettingsStack_profile.h"
#include "SettingsStack_questions.h"
#include "SettingsStack_update.h"

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
  GuiHomeStack_welcome *gui_home_stack_welcome;
  GuiHomeStack_list *gui_home_stack_list;

//  QMap<QString ,GuiChatStack_old*> gui_chat_stack_map;<<

private:
	QMap< GUI::StaticStackType, QWidget*> static_stack_map;
	GUI::StaticStackType current_static_stack_type = GUI::StaticStackType::NULL_Stack;
	void clearStackMap(GUI::StaticStackType &reservation);
	void createStaticStack(GUI::StaticStackType staticStackType);

  QVBoxLayout *main_layout;


public slots:
	void displayStaticStack(GUI::StaticStackType staticStackType);
  void displayChatStack(const QString &usrKey);
//  GuiChatStack_old *addChatStack(UsrProfileStruct *usrProfileStruct);<<

private slots:
  void onMessageToSend(QString *usrKey, QString *message);

signals:
  void sendMessage(QString usrKey, QString message);


};

#endif // GUIMAINBLOCK_H
