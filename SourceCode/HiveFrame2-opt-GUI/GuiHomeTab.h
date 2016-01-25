#ifndef GUIHOMETAB_H
#define GUIHOMETAB_H

#include <QWidget>

#include <GuiTextButton.h>
#include <QVBoxLayout>

class GuiHomeTab : public QWidget
{
  Q_OBJECT

public:
  explicit GuiHomeTab(QWidget *parent = 0);
  ~GuiHomeTab();

  GuiTextButton *welcome_label;
  GuiTextButton *issues_label;
  GuiTextButton *files_label;
  GuiTextButton *settings_label;

public slots:

private:
  QVBoxLayout *main_layout;


};

#endif // GUIHOMETAB_H
