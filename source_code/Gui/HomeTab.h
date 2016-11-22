#ifndef GUIHOMETAB_H
#define GUIHOMETAB_H

#include "Gui/Frameworks/MenuButton.h"

#include <QVBoxLayout>
#include <QGridLayout>

class HomeTab : public QWidget
{
  Q_OBJECT

public:
  explicit HomeTab(QWidget *parent = 0);
  ~HomeTab();

  GuiMenuButton *welcome_btn;
  GuiMenuButton *list_btn;
  GuiMenuButton *storage_btn;

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *button_layout;
};

#endif // GUIHOMETAB_H
