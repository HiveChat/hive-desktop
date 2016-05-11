#ifndef GUIHOMESTACK_LIST_H
#define GUIHOMESTACK_LIST_H

#include "GuiScrollStack.h"
#include "GlobalData.h"

class GuiHomeStack_list : public GuiScrollStack
{
public:
  GuiHomeStack_list(QWidget *parent);

private:
  void addUsr(UsrProfileStruct *usrProfileStruct);

};




#endif // GUIHOMESTACK_LIST_H

