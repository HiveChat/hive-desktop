#ifndef GUIHOMESTACK_LIST_H
#define GUIHOMESTACK_LIST_H

#include "Gui/Frameworks/ScrollStack.h"
#include "Global.h"

class HomeStack_list;
class ListItem;


class ListItem : public QWidget
{
  Q_OBJECT
public:
  explicit ListItem(UsrProfile *profile, QWidget *parent = nullptr);
  ~ListItem();

  void refreshProfile(UsrProfile *profile);

private:
  AvatarButton *avatar_button;
  QLabel *name_label;
  QLabel *ip_label;

};


class HomeStack_list : public ScrollStack
{
  Q_OBJECT

public:
  explicit HomeStack_list(QWidget *parent);
  ~HomeStack_list();

  void addUsr(UsrProfile *usrProfileStruct);
  void refreshUser(UsrProfile *usrProfileStruct);

private:
  QHash<QString, ListItem*> list_item_hash;
};




#endif // GUIHOMESTACK_LIST_H

