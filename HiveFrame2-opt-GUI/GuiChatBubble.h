#ifndef GUICHATBUBBLE_H
#define GUICHATBUBBLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

#include "GuiButton.h"

class GuiChatBubble : public QWidget
{
  Q_OBJECT
public:
  explicit GuiChatBubble(QString text, bool alignLeft, QWidget *parent = 0);

private:
  QHBoxLayout *main_layout;
  QPixmap strip_pixmap;
  QLabel *strip;
  GuiButton *button;


};

#endif // GUICHATBUBBLE_H
