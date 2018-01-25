#ifndef GUIHOMETAB_H
#define GUIHOMETAB_H

#include <QVBoxLayout>
#include <QGridLayout>
#include "Gui/Frameworks/MenuButton.h"

class HomeTab : public QWidget
{
  Q_OBJECT

public:
  explicit HomeTab(QWidget *parent = 0);

  MenuButton *welcome_btn;
  MenuButton *list_btn;
  MenuButton *storage_btn;
};

#endif // GUIHOMETAB_H
