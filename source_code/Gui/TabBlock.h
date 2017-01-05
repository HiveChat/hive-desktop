#ifndef GUITABBLOCK_H
#define GUITABBLOCK_H

#include <QStackedWidget>
#include "Gui/Frameworks/Widgets/LabelButton.h"
#include "ChatTab.h"
#include "HomeTab.h"
#include "SettingsTab.h"


class GuiTabBlock : public QWidget
{
  Q_OBJECT

public:

  explicit GuiTabBlock(QWidget *parent = 0);
  ~GuiTabBlock();

  SettingsTab *settings_tab;
  HomeTab *home_tab;
  ChatTab *chat_tab;

private slots:
  void changeBtnLine();

private:
  int current_tab_index = 0;

  QVBoxLayout *main_layout;
  QGridLayout *tab_label_layout;

  LabelButton *left_tab_label;
  LabelButton *mid_tab_label;
  LabelButton *right_tab_label;

  QFrame *left_btn_line;
  QFrame *mid_btn_line;
  QFrame *right_btn_line;

  QStackedWidget *tab_stacked_widget;



};

#endif // GUITABBLOCK_H
