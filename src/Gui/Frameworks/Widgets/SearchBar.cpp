#include "SearchBar.h"
#include <QDebug>

SearchBar::SearchBar(QWidget *parent)
  : QLineEdit(parent)
  , width(250)
{
  this->setMinimumHeight(32);
  this->setGeometry(x(), y(), width, height());
//  this->setMinimumWidth(250);
//  search_bar->setClearButtonEnabled(true);
//  search_bar->addAction(QIcon("/Users/echo/Downloads/av6584c34aabb39f00a10.png"), QLineEdit::LeadingPosition);
  this->setPlaceholderText("discover...");
  this->setAttribute(Qt::WA_MacShowFocusRect, 0);
//  this->setContentsMargins(10, 0, 0, 10);
  this->setStyleSheet("border-radius: 16px; "
                            "background-color: #eeeeee; "
                            "margin-left: 10px;"
                            "margin-right: 10px;"
                            "padding-left: 10px;"
                      "outline: none;");


  expand_animation = new QVariantAnimation(this);
  expand_animation->setEasingCurve(QEasingCurve::OutQuad);
  expand_animation->setDuration(200);
  expand_animation->setStartValue(width);
  expand_animation->setEndValue(250);
  connect(expand_animation, &QVariantAnimation::valueChanged, this, &SearchBar::updateWidth);

  shrink_animation = new QVariantAnimation(this);
  shrink_animation->setEasingCurve(QEasingCurve::OutQuad);
  shrink_animation->setDuration(200);
  shrink_animation->setStartValue(width);
  shrink_animation->setEndValue(200);
  connect(shrink_animation, &QVariantAnimation::valueChanged, this, &SearchBar::updateWidth);

}

void SearchBar::mousePressEvent(QMouseEvent *)
{
}


void SearchBar::mouseReleaseEvent(QMouseEvent *)
{

}

void SearchBar::enterEvent(QEvent *)
{
  expand_animation->stop();
  shrink_animation->start();
  shrink_animation->setStartValue(width);
}

void SearchBar::leaveEvent(QEvent *)
{
  shrink_animation->stop();
  expand_animation->start();
  expand_animation->setStartValue(width);
}

void SearchBar::updateWidth(const QVariant &v)
{
  width = v.toInt();
  this->setGeometry(x(), y(), width, height());
//  qDebug()<<"set: " << width ;
}
