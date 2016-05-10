#ifndef GUICOMBWIDGET_H
#define GUICOMBWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "GlobalData.h"
#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"

class GuiCombWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCombWidget(UsrProfileStruct *usrProfileStruct, QWidget *parent = 0);
  ~GuiCombWidget();

  UsrProfileStruct usrProfile();
  void setProfile(UsrProfileStruct *usrProfile);


protected:
  void paintEvent(QPaintEvent*);

  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
//  void dragMoveEvent(QEvent *);

private:
  GuiAvatarButton *avatar;
  QLabel *usr_name_label;
  QLabel *ip_addr_label;
  QLabel *status_label;
  QVBoxLayout *usr_info_layout;
  QHBoxLayout *net_status_layout;
  QHBoxLayout *main_layout;

  QString online_str = "<span style=\" color:#39c828;\">●</span>";
  QString offline_str = "<span style=\" color:#ed403f;\">●</span>";


  QPalette hover_palette;
  QColor window_color = GlobalData::g_tabColor;
  QColor default_window_color = GlobalData::g_tabColor;
  QColor hovered_window_color = QColor(255,175,0,161);

  bool selected = false;
  bool hovered  = false;

  ///data
  UsrProfileStruct usr_profile;



signals:
  void clicked(QString usrKey);



};

#endif // GUICOMBWIDGET_H
