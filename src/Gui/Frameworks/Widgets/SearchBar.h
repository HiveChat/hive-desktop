#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include "Gui/Frameworks/Widgets/Button.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QVariantAnimation>

class SearchWidget;
class SearchBar;



class SearchWidget
    : public QLineEdit
{
  Q_OBJECT
public:
  SearchWidget(const int &width, QWidget *parent = nullptr);

  void expand();
  void shrink();
//  void escape();
  void freez(const bool &b);


protected:
  void focusInEvent(QFocusEvent *e);
  void focusOutEvent(QFocusEvent *e);

private:
  void updateWidth(const QVariant &v);

  int width;
  const int width_full = 250;
  const int width_half = 215;
  bool frozen = false;
  QVariantAnimation *expand_anim;
  QVariantAnimation *shrink_anim;

signals:
  void focused(const bool &b);
  void shrinked();
};


class SearchBar
    : public QWidget
{
  Q_OBJECT
public:
  SearchBar(QWidget *parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEnterEvent* e);
  void leaveEvent(QEvent *e);

private:
  int width;
  bool search_focus_lock = false;
  bool settings_toggled = false;
  LabelButton *settings_button;
  SearchWidget *search_widget;
  QHBoxLayout *main_Layout;

signals:
  void settingsSelected(const bool& b);
};

#endif // SEARCHBAR_H
