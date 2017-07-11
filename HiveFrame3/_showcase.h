#ifndef _SHOWCASE_H
#define _SHOWCASE_H

#include "./ui/button.h"
#include <QHBoxLayout>
#include <QLabel>


class _Showcase : public QWidget
{
  Q_OBJECT
public:
  explicit _Showcase(QWidget *parent = nullptr);
  ~_Showcase();

signals:

public slots:

private:
  Button *bt1;
  Button *bt2;

};

#endif // _SHOWCASE_H
