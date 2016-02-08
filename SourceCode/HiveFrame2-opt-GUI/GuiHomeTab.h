#ifndef GUIHOMETAB_H
#define GUIHOMETAB_H

#include <QWidget>

#include "GuiTextButton.h"
#include "GuiLabelButton.h"

#include <QVBoxLayout>
#include <QGridLayout>

class GuiHomeTab : public QWidget
{
  Q_OBJECT

public:
  explicit GuiHomeTab(QWidget *parent = 0);
  ~GuiHomeTab();

  GuiLabelButton *welcome_btn;
  GuiLabelButton *issues_btn;
  GuiLabelButton *files_btn;
  GuiLabelButton *settings_btn;

  GuiTextButton *welcome_label;
  GuiTextButton *issues_label;
  GuiTextButton *files_label;
  GuiTextButton *settings_label;


public slots:

private:

  QGridLayout *main_layout;


};

#endif // GUIHOMETAB_H
