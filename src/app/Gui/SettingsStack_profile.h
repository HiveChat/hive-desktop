#ifndef GUISETTINGSSTACK_PROFILE_H
#define GUISETTINGSSTACK_PROFILE_H

#include "Gui/Frameworks/ScrollStack.h"
#include "Global.h"

#include <QListWidget>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>


class SettingsStack_profile : public ScrollStack
{
  Q_OBJECT

public:
  explicit SettingsStack_profile(QWidget *parent = nullptr);
  ~SettingsStack_profile();

private:
  QHash<QString , QString> avatar_hash;
  QList<QRadioButton *> avatar_radio_btn_list;
  AvatarComposer *avatar_composer;

private slots:
  void onRadioClicked(QAbstractButton *abstractButton);
  void onUsrNameChanged(QString usr_name);
};

#endif // GUISETTINGSSTACK_PROFILE_H
