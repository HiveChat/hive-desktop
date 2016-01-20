#ifndef GUIWELCOMESTACK_H
#define GUIWELCOMESTACK_H

#include <GuiLabelButton.h>

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

class GuiWelcomeStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiWelcomeStack(QWidget *parent = 0);

private:
  QVBoxLayout *main_layout;
  QHBoxLayout *bottom_layout;
  GuiLabelButton *icon_label;
  QPixmap icon_pixmap;

};

#endif // GUIWELCOMESTACK_H
