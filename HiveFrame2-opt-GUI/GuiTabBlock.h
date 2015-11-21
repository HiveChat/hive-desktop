#ifndef GUITABBLOCK_H
#define GUITABBLOCK_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QLabel>
#include <QImage>
#include <QStackedWidget>

#include "GuiTabLabel.h"

#include "GuiChatTab.h"
#include "GuiHomeTab.h"

class GuiTabBlock : public QWidget
{
  Q_OBJECT

public:

  explicit GuiTabBlock(QWidget *parent = 0);
  ~GuiTabBlock();

  QVBoxLayout *main_layout;
  QHBoxLayout *window_btn_layout;
  QGridLayout *tab_label_layout;

  GuiTabLabel *exit_hint;
  GuiTabLabel *min_hint;
  GuiTabLabel *max_hint;

  GuiTabLabel *left_tab_label;
  GuiTabLabel *mid_tab_label;
  GuiTabLabel *right_tab_label;

  QLabel *left_btn_line_label;
  QLabel *mid_btn_line_label;
  QLabel *right_btn_line_label;

  QStackedWidget *tab_stacked_widget;
  GuiHomeTab *gui_home_tab;
  GuiChatTab *gui_chat_tab;


  int currentIndex();


private slots:
  void changeBtnLine();
  void changeWindowBtn();
  void recoverWindowBtn();

private:
  int current_tab_index = 0;

  QImage left_btn_line_label0;
  QImage left_btn_line_label1;
  QImage mid_btn_line_label0;
  QImage mid_btn_line_label1;
  QImage right_btn_line_label0;
  QImage right_btn_line_label1;

  QPixmap exit_hint_img0;
  QPixmap exit_hint_img1;
  QPixmap min_hint_img0;
  QPixmap min_hint_img1;
  QPixmap max_hint_img0;
  QPixmap max_hint_img1;


};

#endif // GUITABBLOCK_H
