#include "GuiOSXNotification.h"
#include <QDebug>

GuiOSXNotification::GuiOSXNotification(QWidget *parent) :
    QWidget(parent)
{
  this->setFixedHeight(65);
  this->setFixedWidth(325);

  startPoint = QPoint(desktop.availableGeometry().width()+this->width(), 40);
  endPoint = QPoint(desktop.availableGeometry().width()-this->width()-20, 40);

  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  this->move(startPoint);
  showAnimation();

  this->setAttribute(Qt::WA_TranslucentBackground);



}

GuiOSXNotification::~GuiOSXNotification()
{

}

void GuiOSXNotification::showAnimation(){
  animation = new QPropertyAnimation(this,"pos");
  animation->setDuration(1000);
  animation->setStartValue(startPoint);
  animation->setEndValue(endPoint);
  animation->start();

  remainTimer = new QTimer();
  connect(remainTimer,SIGNAL(timeout()),this,SLOT(closeAnimation()));
  remainTimer->start(5000);
}

void GuiOSXNotification::closeAnimation(){
    //清除Timer指针和信号槽
    remainTimer->stop();
    disconnect(remainTimer,SIGNAL(timeout()),this,SLOT(closeAnimation()));
    delete remainTimer;
    remainTimer = NULL;

    //弹出框回去动画
    animation->setStartValue(QPoint(this->x(),this->y()));
    animation->setEndValue(startPoint);
    animation->start();
    //弹回动画完成后清理动画指针
    connect(animation,SIGNAL(finished()),this,SLOT(clearAll()));
}

//清理动画指针
void GuiOSXNotification::clearAll(){
  disconnect(animation,SIGNAL(finished()),this,SLOT(clearAll()));
  delete animation;
  animation=NULL;

  this->close();
}



void GuiOSXNotification::paintEvent(QPaintEvent*)
{
  QRectF rectangle(0, 0, this->width(), this->height());
  QPainter paint(this);
  paint.setPen(QPen(Qt::NoPen));
  paint.setBrush(QBrush(QColor(240,240,240,205),Qt::SolidPattern));
  paint.drawRoundedRect(rectangle,5,5);
}
