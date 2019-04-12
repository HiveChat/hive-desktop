#include "SearchBar.h"
#include <QDebug>

SearchWidget::SearchWidget(const int& width, QWidget *parent)
  : QLineEdit(parent)
  , width(width)
{
  this->setMinimumHeight(32);
  this->setGeometry(x(), y(), width, height());
//  search_bar->addAction(QIcon("/Users/echo/Downloads/av6584c34aabb39f00a10.png"), QLineEdit::LeadingPosition);
  this->setPlaceholderText("discover...");
  this->setAttribute(Qt::WA_MacShowFocusRect, 0);
//  this->setContentsMargins(10, 0, 0, 10);
  this->setStyleSheet("border-radius: 16px; "
                      "background-color: #eeeeee; "
                      "margin-left: 10px;"
                      "margin-right: 10px;"
                      "padding-left: 10px;"
                      "padding-right: 10px;"
                      "outline: none;");


  expand_animation = new QVariantAnimation(this);
  expand_animation->setEasingCurve(QEasingCurve::OutElastic);
  expand_animation->setDuration(500);
  expand_animation->setStartValue(width);
  expand_animation->setEndValue(250);
  connect(expand_animation, &QVariantAnimation::valueChanged, this, &SearchWidget::updateWidth);

  shrink_animation = new QVariantAnimation(this);
  shrink_animation->setEasingCurve(QEasingCurve::OutQuad);
  shrink_animation->setDuration(200);
  shrink_animation->setStartValue(width);
  shrink_animation->setEndValue(225);
  connect(shrink_animation, &QVariantAnimation::valueChanged, this, &SearchWidget::updateWidth);
  connect(shrink_animation, &QVariantAnimation::finished, this, &SearchWidget::shrinked);
}

void SearchWidget::expand()
{
  shrink_animation->stop();
  expand_animation->start();
  expand_animation->setStartValue(width);
}

void SearchWidget::shrink()
{
  expand_animation->stop();
  shrink_animation->start();
  shrink_animation->setStartValue(width);
}

void SearchWidget::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  qWarning()<<"--------------------SearchWidget::focusInEvent";

  emit focused(true);
}

void SearchWidget::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  qWarning()<<"--------------------SearchWidget::focusOutEvent";
  emit focused(false);
}

void SearchWidget::updateWidth(const QVariant &v)
{
  width = v.toInt();
  this->setGeometry(x(), y(), width, height());
//  qDebug()<<"set: " << width ;
}




SearchBar::SearchBar(QWidget *parent)
  : QWidget(parent)
  , width(250)
{
  settings_button = new LabelButton(0, this);
  settings_button->setHidden(true);
  settings_button->setDefaultPixmap("/Users/echo/Downloads/settings_0.png");
  settings_button->setHoveredPixmap("/Users/echo/Downloads/settings_1.png");
  connect(settings_button, &LabelButton::clicked, this, &SearchBar::settingsClicked);

  search_widget = new SearchWidget(width, this);
  connect(search_widget, &SearchWidget::focused, [this](const bool &b){
      search_focus_lock = b;
      if(!search_focus_lock)
        {
          settings_button->setHidden(true);
          search_widget->expand();
        }
    });
  connect(search_widget, &SearchWidget::shrinked, [this](){
      settings_button->setHidden(false);
    });

  main_Layout = new QHBoxLayout(this);
  main_Layout->setContentsMargins(0,0,0,0);
  main_Layout->setSpacing(3);
  main_Layout->addWidget(search_widget);
  main_Layout->addWidget(settings_button);


}

void SearchBar::mousePressEvent(QMouseEvent *)
{
}


void SearchBar::mouseReleaseEvent(QMouseEvent *)
{

}

void SearchBar::enterEvent(QEvent *)
{
  if(animation_lock || search_focus_lock)
    return;
  search_widget->shrink();
}

void SearchBar::leaveEvent(QEvent *)
{
  if(animation_lock || search_focus_lock)
    return;
  settings_button->setHidden(true);
  search_widget->expand();
}






