#ifndef GUIMENUBUTTON_H
#define GUIMENUBUTTON_H

#include "GlobalData.h"

#include <QLabel>
#include <QMouseEvent>
#include <QHBoxLayout>


class MenuButton : public QWidget
{
  Q_OBJECT

public:
  explicit MenuButton(QString text, GUI::StaticStackType staticStackType, QWidget *parent = 0);
  ~MenuButton();

  void setDefaultPixmap(QString path);
  void setHoveredPixmap(QString path);

protected:

  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  GUI::StaticStackType static_stack_type;

  QLabel *icon_label;
  QLabel *text_label;

  QPixmap default_pixmap;
  QPixmap hovered_pixmap;
  QPalette text_palette;
  QColor default_text_color = QColor(100,100,100);
  QColor hovered_text_color = QColor(255,181,0);

  void setDefault();
  void setHovered();


signals:
  void clicked(GUI::StaticStackType);

};

#endif // GUIMENUBUTTON_H
