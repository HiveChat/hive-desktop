#ifndef GUICOMBWIDGET_H
#define GUICOMBWIDGET_H

#include <QWidget>
#include <QLabel>
#include <GuiLabelButton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <GuiAvatarButton.h>

class GuiCombWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCombWidget(QString avatarPath, QString usrName, QString ipAddr, QWidget *parent = 0);
  ~GuiCombWidget();

protected:
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

  bool selected = false;
  bool hovered  = false;

  //QFont usr_name_font;
  //QFont ip_addr_font;

};

#endif // GUICOMBWIDGET_H
