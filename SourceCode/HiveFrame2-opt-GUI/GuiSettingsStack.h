#ifndef GUISETTINGSSTACK_H
#define GUISETTINGSSTACK_H

#include "GuiAvatarButton.h"

#include <QWidget>

////////top
class GuiSettingsStack_top_bar : public QWidget
{
  Q_OBJECT

public:
  explicit GuiSettingsStack_top_bar(QWidget *parent = 0);
  ~GuiSettingsStack_top_bar();

signals:

public slots:
};

////////main
class GuiSettingsStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiSettingsStack(QWidget *parent = 0);
  ~GuiSettingsStack();

signals:

public slots:
};

#endif // GUISETTINGSSTACK_H
