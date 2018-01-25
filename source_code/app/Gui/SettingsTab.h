#ifndef GUISETTINGSTAB_H
#define GUISETTINGSTAB_H

#include "Gui/Frameworks/MenuButton.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>

class SettingsTab : public QWidget
{
  Q_OBJECT

public:
  explicit SettingsTab(QWidget *parent = 0);
  ~SettingsTab();

  MenuButton *profile_btn;
  MenuButton *messaging_btn;
  MenuButton *style_btn;
  MenuButton *questions_btn;
  MenuButton *update_btn;

private:
  QVBoxLayout *main_layout;
};

#endif // GUISETTINGSTAB_H
