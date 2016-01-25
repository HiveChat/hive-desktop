#ifndef GUIMAINBLOCK_H
#define GUIMAINBLOCK_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>

#include "GuiChatStack.h"
#include "GuiWelcomeStack.h"

class GuiMainBlock : public QWidget
{
  Q_OBJECT

public:
  explicit GuiMainBlock(QWidget *parent = 0);
  ~GuiMainBlock();

  GuiChatStack *gui_chat_stack;
  GuiWelcomeStack *gui_welcome_stack;
  QStackedWidget *main_stacked_widget;

private:
  QVBoxLayout *main_layout;

public slots:
  void displayChatStack(QString usrKey);
  void displayWelcomeStack();
  void addChatStack(QStringList usrInfoStrList);
  void setCurrentStack(QWidget *widget);
  void onMessageRecieved(QStringList message_str_list);

signals:
  void whoIs(QString usrKey);
  void whoseMessage(QStringList message_str_list);


};

#endif // GUIMAINBLOCK_H
