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

protected:
  void focusInEvent(QFocusEvent *e);
  void focusOutEvent(QFocusEvent *e);

private:
  void updateWidth(const QVariant &v);


  int width;
  QVariantAnimation *expand_animation;
  QVariantAnimation *shrink_animation;

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
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  int width;
  bool search_focus_lock = false;
  bool animation_lock = false;

  LabelButton *settings_button;
  SearchWidget *search_widget;
  QHBoxLayout *main_Layout;

signals:
  void settingsClicked();
};

#endif // SEARCHBAR_H
