#ifndef GUIMENUBUTTON_H
#define GUIMENUBUTTON_H

#include <QLabel>
#include <QMouseEvent>
#include <QHBoxLayout>

class GuiMenuButton : public QWidget
{
  Q_OBJECT

public:
  explicit GuiMenuButton(QString text, QWidget *parent = 0);
  ~GuiMenuButton();

  void setDefaultPixmap(QString path);
  void setHoveredPixmap(QString path);

protected:

  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  QLabel *icon_label;
  QLabel *text_label;
  QHBoxLayout *main_layout;

  QPixmap default_pixmap;
  QPixmap hovered_pixmap;
  QPalette text_palette;
  QColor default_text_color = QColor(150,150,150);
  QColor hovered_text_color = QColor(255,181,0);

  void setDefault();
  void setHovered();


signals:
  void clicked();

};

#endif // GUIMENUBUTTON_H
