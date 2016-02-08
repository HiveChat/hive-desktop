#ifndef GUICHATSTACK_H
#define GUICHATSTACK_H

#include "DataHistoryIO.h"
#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"
#include "GuiChatBubble.h"
#include "GlobalData.h"


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QTextEdit>
#include <QScrollArea>



//////////////////////////top//////////////////////////////////////

class GuiChatStack_top_bar : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_top_bar(QStringList usrInfoStrList, QWidget *parent = 0);
  ~GuiChatStack_top_bar();

private:
  QHBoxLayout *main_layout;
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
  explicit GuiChatStack_message_editor(QWidget *parent = 0);
  ~GuiChatStack_message_editor();

  GuiLabelButton *send_btn;
  QTextEdit *text_editor;

protected:
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

private:
  QVBoxLayout *edit_layout;
  QHBoxLayout *tool_layout;

  GuiLabelButton *expression_label;
  GuiLabelButton *image_label;
  GuiLabelButton *file_label;

  QHBoxLayout *main_layout;

};

//////////////////////////main//////////////////////////////////////

class GuiChatStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack(QStringList usrInfoStrList, QWidget *parent = 0);
  ~GuiChatStack();

  GuiChatStack_top_bar *top_bar;
  GuiChatStack_chat_widget *chat_widget;
  GuiChatStack_message_editor *message_editor;

private:
  DataHistoryIO *data_history_io;
  int current_active_index;

  QVBoxLayout *main_layout;
  QScrollArea *chat_scroll_area;

  QStringList usr_info_str_list;

  void refreshCurrentActiveIndex();

public slots:
  void checkMessage(QStringList message_str_list, bool fromMe);
  void onSendButtonClicked();
  void loadHistory(int index);

signals:
  void sendMessage(QString usrKey, QString message);

};






#endif // GUICHATSTACK_H
