#ifndef GUIHOMESTACK_LIST_H
#define GUIHOMESTACK_LIST_H

#include "Gui/Frameworks/ScrollStack.h"
#include "GlobalData.h"

class GuiHomeStack_list;
class GuiListItem;


class GuiListItem : public QWidget
{
  Q_OBJECT
public:
  explicit GuiListItem(UsrProfileStruct *usrProfileStruct, QWidget *parent = 0);
  ~GuiListItem();

  void refreshUsrProfile(UsrProfileStruct *usrProfileStruct);

private:
  GuiAvatarButton *avatar_button;
  QLabel *name_label;
  QLabel *ip_label;

};


class GuiHomeStack_list : public ScrollStack
{
  Q_OBJECT

public:
  explicit GuiHomeStack_list(QWidget *parent);
  ~GuiHomeStack_list();

  void addUsr(UsrProfileStruct *usrProfileStruct);
  void refreshUsrProfile(UsrProfileStruct *usrProfileStruct);

private:
  QHash<QString, GuiListItem*> list_item_hash;
};




#endif // GUIHOMESTACK_LIST_H

