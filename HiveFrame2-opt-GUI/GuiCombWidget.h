#ifndef GUICOMBWIDGET_H
#define GUICOMBWIDGET_H

#include <QWidget>
#include <QLabel>
#include <GuiLabelButton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include <GuiAvatarButton.h>

class GuiCombWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCombWidget(QString avatarPath, QString usrName, QString ipAddr, QWidget *parent = 0);
  ~GuiCombWidget();

  void setEntered(bool entered);

protected:
  void paintEvent(QPaintEvent*);

  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  GuiAvatarButton *avatar;
  QLabel *usr_name_label;
  QLabel *ip_addr_label;
  QLabel *status_label;
  QVBoxLayout *usr_info_layout;
  QHBoxLayout *ip_status_layout;
  QHBoxLayout *main_layout;

  QPalette hover_palette;
  QColor window_color = QColor(255,255,255);
  QColor default_window_color = QColor(255,255,255);
  QColor hovered_window_color = QColor(255,232,166);

  bool selected = false;
  bool hovered  = false;

  //QFont usr_name_font;
  //QFont ip_addr_font;

signals:
  void entered();


};

#endif // GUICOMBWIDGET_H
