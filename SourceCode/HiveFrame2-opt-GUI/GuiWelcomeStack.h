#ifndef GUIWELCOMESTACK_H
#define GUIWELCOMESTACK_H

#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QPixmap>

class GuiWelcomeStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiWelcomeStack(QWidget *parent = 0);

private:
  QHBoxLayout *bottom_layout;
  QVBoxLayout *profile_layout;

  QWidget *profile_widget;
  QLabel *usr_name_label;
  QLabel *welcome_label;
  QLabel *ip_label;
  QLabel *host_name_label;

  GuiAvatarButton *my_avatar;
  GuiLabelButton *background_label;

  QPixmap icon_pixmap;

};

#endif // GUIWELCOMESTACK_H
