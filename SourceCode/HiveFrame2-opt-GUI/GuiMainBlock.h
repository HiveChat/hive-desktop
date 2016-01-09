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
  void addChatStack(QStringList usrInfoStrList);
  void setCurrentStack(QWidget *widget);



};

#endif // GUIMAINBLOCK_H
