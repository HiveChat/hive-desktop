#include "hiveswitch.h"

HiveSwitch::HiveSwitch(QWidget *parent)
  : QWidget(parent)
{
  slot_pixmap.load(":/img/img/slot.png");
  slot_pixmap.setDevicePixelRatio(2.0);
  this->setFixedSize(slot_pixmap.width()/2,slot_pixmap.height()/2);



  switch_pixmap.load(":/img/img/switch.png");
  switch_pixmap.setDevicePixelRatio(2.0);
  switch_label = new QLabel(this);
  switch_label->setPixmap(switch_pixmap);


  QStateMachine *machine = new QStateMachine;

  QState *state1 = new QState(machine);
  state1->assignProperty(switch_label,"geometry",QRect(0,-16,switch_pixmap.width(), switch_pixmap.height()));
  machine->setInitialState(state1);

  QState *state2 = new QState(machine);
  state2->assignProperty(switch_label,"geometry",QRect(22,-16,switch_pixmap.width(), switch_pixmap.height()));

  QPropertyAnimation *animation=new QPropertyAnimation(switch_label,"geometry");
  animation->setDuration(100);
  animation->setEasingCurve(QEasingCurve::InCubic);

  QSignalTransition *transition1=state1->addTransition(this,SIGNAL(clicked()),state2);
  transition1->addAnimation(animation);
  QSignalTransition *transition2=state2->addTransition(this,SIGNAL(clicked()),state1);
  transition2->addAnimation(animation);
  machine->start();
}

HiveSwitch::~HiveSwitch()
{

}

void HiveSwitch::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(0,0,slot_pixmap);

}

void HiveSwitch::mouseReleaseEvent(QMouseEvent *event)
{
  emit clicked();
}

