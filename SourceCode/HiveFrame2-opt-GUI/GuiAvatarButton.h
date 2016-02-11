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
  GuiAvatarButton(QString path, int Diameter, QWidget *parent);
  void setAvatar(QString path);

protected:
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  int diameter;

signals:
  void clicked();


};

#endif // GUIAVATARBUTTON_H
