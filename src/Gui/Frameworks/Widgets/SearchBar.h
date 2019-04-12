#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>
#include <QMouseEvent>
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

private:
  void updateWidth(const QVariant &v);

  int width;
  QVariantAnimation *expand_animation;
  QVariantAnimation *shrink_animation;
};

#endif // SEARCHBAR_H
