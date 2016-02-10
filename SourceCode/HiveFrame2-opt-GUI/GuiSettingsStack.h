#ifndef GUISETTINGSSTACK_H
#define GUISETTINGSSTACK_H

#include "GuiAvatarButton.h"

#include <QWidget>


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
