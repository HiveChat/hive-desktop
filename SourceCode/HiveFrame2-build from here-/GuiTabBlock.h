#ifndef GUITABBLOCK_H
#define GUITABBLOCK_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QPixmap>
#include <QStackedWidget>

#include "GuiLabelButton.h"

#include "GuiChatTab.h"
#include "GuiHomeTab.h"
#include "GuiSettingsTab.h"


class GuiTabBlock : public QWidget
{
  Q_OBJECT

public:

  explicit GuiTabBlock(QWidget *parent = 0);
  ~GuiTabBlock();

  QVBoxLayout *main_layout;
  QGridLayout *tab_label_layout;

  GuiLabelButton *left_tab_label;
  GuiLabelButton *mid_tab_label;
  GuiLabelButton *right_tab_label;

  QFrame *left_btn_line;
  QFrame *mid_btn_line;
  QFrame *right_btn_line;

  QStackedWidget *tab_stacked_widget;
  GuiHomeTab *gui_home_tab;
  GuiChatTab *gui_chat_tab;
  GuiSettingsTab *gui_settings_tab;


  int currentIndex();


private slots:
  void changeBtnLine();

private:
  int current_tab_index = 0;




};

#endif // GUITABBLOCK_H
