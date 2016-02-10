#ifndef GUISCROLLSTACK_H
#define GUISCROLLSTACK_H

#include <QVBoxLayout>
#include <QScrollArea>
#include <GuiAvatarButton.h>


class GuiScrollStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiScrollStack(QString imgPath, QString title, QString subTitle, QWidget *centralWidget, QWidget *parent = 0);
  ~GuiScrollStack();
};

#endif // GUISCROLLSTACK_H
