#ifndef GUIWELCOMESTACK_H
#define GUIWELCOMESTACK_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>

class GuiWelcomeStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiWelcomeStack(QWidget *parent = 0);

private:
  QVBoxLayout *main_layout;
  QLabel *icon_label;
  QPixmap icon_pixmap;

};

#endif // GUIWELCOMESTACK_H
