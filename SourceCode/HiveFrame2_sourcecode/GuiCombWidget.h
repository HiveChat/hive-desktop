#ifndef GUICOMBWIDGET_H
#define GUICOMBWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHostAddress>

#include "GlobalType.h"
#include "GlobalData.h"
#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"
#include "GuiBadgeIcon.h"

class GuiCombWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCombWidget(UsrProfileStruct *usrProfileStruct, QWidget *parent = 0);
  ~GuiCombWidget();

  void setProfile(UsrProfileStruct *usrProfile);
  void setBadgeNumber(const int &num);

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
  GuiBadgeIcon *badge_icon;
  QVBoxLayout *usr_info_layout;
  QHBoxLayout *net_status_layout;
  QHBoxLayout *main_layout;

  QString online_str = "<span style=\" color:#39c828;\">●</span>";
  QString offline_str = "<span style=\" color:#ed403f;\">●</span>";
  QString unstable_str = "<span style=\" color:#ffb500;\">●</span>";


  QPalette hover_palette;
  QColor window_color = GlobalData::color_tab;
  QColor default_window_color = GlobalData::color_tab;
  QColor hovered_window_color = QColor(255,175,0,161);

  bool selected = false;
  bool hovered  = false;

  ///data
  UsrProfileStruct usr_profile;

  QString getSubNetStr(QString &ipAddr);



signals:
  void clicked(QString usrKey);



};

#endif // GUICOMBWIDGET_H
