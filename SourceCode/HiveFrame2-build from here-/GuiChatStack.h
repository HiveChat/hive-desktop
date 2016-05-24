#ifndef GUICHATSTACK_H
#define GUICHATSTACK_H

#include "DataHistoryIO.h"
#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"
#include "GuiChatBubble.h"
#include "GlobalData.h"

#include <QScrollBar>
#include <QTextEdit>
#include <QScrollArea>


class GuiChatStack_top_bar;
class GuiChatStack_chat_widget;
class GuiChatStack_message_editor;
class GuiChatStack;


//////////////////////////top//////////////////////////////////////

class GuiChatStack_top_bar : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_top_bar(UsrProfileStruct *usrProfileStruct, QWidget *parent = 0);
  ~GuiChatStack_top_bar();

  void setProfile(UsrProfileStruct *usrProfileStruct);

private:
  QHBoxLayout *main_layout;
  QLabel *usr_name_label;
  QLabel *usr_ip_label;
  GuiAvatarButton *avatar_button;

};

//////////////////////////mid//////////////////////////////////////

class GuiChatStack_chat_widget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_chat_widget(QWidget *parent = 0);
  ~GuiChatStack_chat_widget();

  void clearChatBubbles();

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *chat_bubble_layout;
  GuiChatBubble *gui_chat_bubble;

  QList<GuiChatBubble*> chat_bubble_list;

public slots:
  void addChatBubble(QString message, bool fromMe);

};

//////////////////////////bottom//////////////////////////////////////

class GuiChatStack_message_editor : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_message_editor(QString *usrKey, QWidget *parent = 0);
  ~GuiChatStack_message_editor();

  GuiLabelButton *send_btn;
  QTextEdit *text_editor;

protected:
  bool eventFilter(QObject *obj, QEvent *e);

private:
  QVBoxLayout *edit_layout;
  QHBoxLayout *tool_layout;

  GuiLabelButton *expression_label;
  GuiLabelButton *image_label;
  GuiLabelButton *file_label;

  QHBoxLayout *main_layout;


  QString usr_key;
signals:
  void sendMessage(QString *usrKey, QString *message);

};

//////////////////////////main//////////////////////////////////////

class GuiChatStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack(UsrProfileStruct *usrProfileStruct, QWidget *parent = 0);
  ~GuiChatStack();

  void refreshUsrProfile(UsrProfileStruct *usrProfileStruct);
  void checkMessage(MessageStruct messageStruct, bool fromMe);

  GuiChatStack_top_bar *top_bar;
  GuiChatStack_chat_widget *chat_widget;
  GuiChatStack_message_editor *message_editor;

private:
  DataHistoryIO *data_history_io;
  int current_active_index;

  QVBoxLayout *main_layout;
  QScrollArea *chat_scroll_area;

  UsrProfileStruct usr_profile;

  void loadHistory(int index);
  void refreshCurrentActiveIndex();

public slots:
  void onSendButtonClicked();

signals:
  void sendMessage(QString *usrKey, QString *message);

};






#endif // GUICHATSTACK_H
