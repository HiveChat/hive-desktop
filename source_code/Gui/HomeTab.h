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

  MenuButton *welcome_btn;
  MenuButton *list_btn;
  MenuButton *storage_btn;

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *button_layout;
};

#endif // GUIHOMETAB_H
