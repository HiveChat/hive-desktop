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

  GuiMenuButton *profile_btn;
  GuiMenuButton *messaging_btn;
  GuiMenuButton *style_btn;
  GuiMenuButton *questions_btn;
  GuiMenuButton *update_btn;

private:
  QVBoxLayout *main_layout;
};

#endif // GUISETTINGSTAB_H
