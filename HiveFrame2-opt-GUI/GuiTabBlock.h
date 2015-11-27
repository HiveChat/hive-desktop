#ifndef GUITABBLOCK_H
#define GUITABBLOCK_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QLabel>
#include <QPixmap>
#include <QStackedWidget>

#include "GuiLabelButton.h"

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

  GuiLabelButton *exit_hint;
  GuiLabelButton *min_hint;
  GuiLabelButton *max_hint;

  GuiLabelButton *left_tab_label;
  GuiLabelButton *mid_tab_label;
  GuiLabelButton *right_tab_label;

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

  QPixmap left_btn_line_label0;
  QPixmap left_btn_line_label1;
  QPixmap mid_btn_line_label0;
  QPixmap mid_btn_line_label1;
  QPixmap right_btn_line_label0;
  QPixmap right_btn_line_label1;

  QPixmap exit_hint0;
  QPixmap exit_hint1;
  QPixmap min_hint0;
  QPixmap min_hint1;
  QPixmap max_hint0;
  QPixmap max_hint1;


  //for GuiLabelButton::setHDPixmap(QString path)
  /*QString exit_hint0 = ":/img/img/exit_hint_0.png";
  QString exit_hint1 = ":/img/img/exit_hint_1.png";
  QString min_hint0 = ":/img/img/min_hint_0.png";
  QString min_hint1 = ":/img/img/min_hint_1.png";
  QString max_hint0 = ":/img/img/max_hint_0.png";
  QString max_hint1 = ":/img/img/max_hint_1.png";*/


};

#endif // GUITABBLOCK_H
