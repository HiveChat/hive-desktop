#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QVariantAnimation>

class SearchBar
    : public QLineEdit
{
public:
  SearchBar(QWidget *parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void focusInEvent(QFocusEvent *e);
  void focusOutEvent(QFocusEvent *e);

private:
  void updateWidth(const QVariant &v);

  int width;
  bool animation_lock = false;
  QVariantAnimation *expand_animation;
  QVariantAnimation *shrink_animation;
};

#endif // SEARCHBAR_H
