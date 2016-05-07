#ifndef GUISETTINGSSTACK_PROFILE_H
#define GUISETTINGSSTACK_PROFILE_H

#include "GuiScrollStack.h"
#include "GuiColorPicker.h"
#include "GlobalData.h"

#include <QListWidget>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>


class GuiSettingsStack_profile : public GuiScrollStack
{
  Q_OBJECT

public:
  explicit GuiSettingsStack_profile(QWidget *parent = 0);
  ~GuiSettingsStack_profile();

private:
  QMap<QString , QString> avatar_map;
  QList<QRadioButton *> avatar_radio_btn_list;
  GuiAvatarButton *avatar_btn;

private slots:
  void onRadioClicked(QAbstractButton *abstractButton);
  void onUsrNameChanged(QString usr_name);
};

#endif // GUISETTINGSSTACK_PROFILE_H
