#ifndef GUISETTINGSTAB_H
#define GUISETTINGSTAB_H

#include "GuiMenuButton.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>

class GuiSettingsTab : public QWidget
{
  Q_OBJECT

public:
  explicit GuiSettingsTab(QWidget *parent = 0);
  ~GuiSettingsTab();

  GuiMenuButton *profile_btn;
  GuiMenuButton *messaging_btn;
  GuiMenuButton *style_btn;
  GuiMenuButton *questions_btn;

private:
  QVBoxLayout *main_layout;
};

#endif // GUISETTINGSTAB_H
