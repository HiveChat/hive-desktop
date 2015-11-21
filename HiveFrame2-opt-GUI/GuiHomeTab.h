#ifndef GUIHOMETAB_H
#define GUIHOMETAB_H

#include <QWidget>

#include <GuiTabLabel.h>
#include <QVBoxLayout>

class GuiHomeTab : public QWidget
{
  Q_OBJECT

public:
  explicit GuiHomeTab(QWidget *parent = 0);
  ~GuiHomeTab();

public slots:

private:
  QVBoxLayout *main_layout;

  GuiTabLabel *welcome_label;
  GuiTabLabel *issues_label;
  GuiTabLabel *files_label;
  GuiTabLabel *settings_label;
};

#endif // GUIHOMETAB_H
