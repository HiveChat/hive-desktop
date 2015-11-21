#ifndef GUIHOMEBTN_H
#define GUIHOMEBTN_H

#include <QPushButton>

class GuiHomeBtn : public QPushButton
{
public:
  explicit GuiHomeBtn();
  ~GuiHomeBtn();

protected:
  void paintEvent(QPainter*);
};

#endif // GUIHOMEBTN_H
