#ifndef GUIAVATARBUTTON_H
#define GUIAVATARBUTTON_H

#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>


class GuiAvatarButton : public QLabel
{
  Q_OBJECT

public:
  GuiAvatarButton(QString path, int Diameter, int borderWidth, QWidget *parent);


protected:
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:


  int diameter;
  int border_width;


};

#endif // GUIAVATARBUTTON_H
