#ifndef GUICHATSTACK_H
#define GUICHATSTACK_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QTextEdit>
#include <QScrollArea>

#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"
#include "GuiChatBubble.h"

//////////////////////////top//////////////////////////////////////

class GuiChatStack_top_bar : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_top_bar(QWidget *parent = 0);
  ~GuiChatStack_top_bar();

private:
  QHBoxLayout *main_layout;
  GuiAvatarButton *avatar_label;

};

//////////////////////////mid//////////////////////////////////////

class GuiChatStack_chat_widget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_chat_widget(QWidget *parent = 0);
  ~GuiChatStack_chat_widget();

private:

  QVBoxLayout *main_layout;
  GuiChatBubble *gui_chat_bubble;

};

//////////////////////////bottom//////////////////////////////////////

class GuiChatStack_message_editor : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_message_editor(QWidget *parent = 0);
  ~GuiChatStack_message_editor();

private:
  QTextEdit *text_editor;
  QVBoxLayout *edit_layout;
  QHBoxLayout *tool_layout;

  GuiLabelButton *expression_label;
  GuiLabelButton *image_label;
  GuiLabelButton *file_label;

  GuiLabelButton *send_btn;

  QHBoxLayout *main_layout;

};

//////////////////////////main//////////////////////////////////////

class GuiChatStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack(QWidget *parent = 0);
  ~GuiChatStack();

signals:

public slots:

private:
  QVBoxLayout *main_layout;

  GuiChatStack_top_bar *top_bar;
  GuiChatStack_chat_widget *chat_widget;
  GuiChatStack_message_editor *message_editor;

  QScrollArea *chat_scroll_area;

};






#endif // GUICHATSTACK_H
