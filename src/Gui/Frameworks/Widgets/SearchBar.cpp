#include "SearchBar.h"

#include <QIcon>

#include <QDebug>

SearchWidget::SearchWidget(const int& width, QWidget *parent)
  : QLineEdit(parent)
  , width(width)
{
  this->setMinimumHeight(32);
  this->setGeometry(x(), y(), width, height());
  this->setPlaceholderText("discover...");
  this->setAttribute(Qt::WA_MacShowFocusRect, 0);
  this->setStyleSheet("border-radius: 16px; "
                      "background-color: #eeeeee; "
                      "margin-left: 10px;"
                      "margin-right: 10px;"
                      "padding-left: 10px;"
                      "padding-right: 10px;"
                      "outline: none;");

  expand_anim = new QVariantAnimation(this);
  expand_anim->setEasingCurve(QEasingCurve::OutElastic);
  expand_anim->setDuration(500);
  expand_anim->setEndValue(width_full);
  connect(expand_anim, &QVariantAnimation::valueChanged, this, &SearchWidget::updateWidth);

  shrink_anim = new QVariantAnimation(this);
  shrink_anim->setEasingCurve(QEasingCurve::OutQuad);
  shrink_anim->setDuration(200);
  shrink_anim->setEndValue(width_half);
  connect(shrink_anim, &QVariantAnimation::valueChanged, this, &SearchWidget::updateWidth);
  connect(shrink_anim, &QVariantAnimation::finished, this, &SearchWidget::shrinked);

}

void SearchWidget::expand()
{
  if(frozen)
    return;
  shrink_anim->stop();
  expand_anim->setStartValue(width);
  expand_anim->start();
}

void SearchWidget::shrink()
{
  if(frozen)
    return;
  expand_anim->stop();
  shrink_anim->setStartValue(width);
  shrink_anim->start();
}

void SearchWidget::freez(const bool &b)
{
  frozen = b;
}

void SearchWidget::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  if(!frozen)
    emit focused(true);
}

void SearchWidget::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  if(!frozen)
    emit focused(false);
}

void SearchWidget::updateWidth(const QVariant &v)
{
  width = v.toInt();
  this->setGeometry(x(), y(), width, height());
}




SearchBar::SearchBar(QWidget *parent)
  : QWidget(parent)
  , width(250)
{
  settings_button = new LabelButton(0, this);
  settings_button->setHidden(true);
  settings_button->setDefaultPixmap(":/img/img/settings_0.png");
  settings_button->setHoveredPixmap(":/img/img/settings_1.png");
  connect(settings_button, &LabelButton::clicked, [this] {
      if(settings_toggled)
        {
          settings_toggled = false;
          settings_button->setDefaultPixmap(":/img/img/settings_0.png");
          settings_button->setHoveredPixmap(":/img/img/settings_1.png");
          search_widget->freez(false);
          search_widget->shrink();
          search_widget->setHidden(false);
          emit settingsSelected(false);
        }
      else
        {
          settings_toggled = true;
          settings_button->setDefaultPixmap(":/img/img/chat_0.png");
          settings_button->setHoveredPixmap(":/img/img/chat_1.png");
          search_widget->freez(true);
          emit settingsSelected(true);
        }
    });

  search_widget = new SearchWidget(width, this);
  connect(search_widget, &SearchWidget::focused, [this](const bool &b){
      search_focus_lock = b;
      if(!b)
        {
          settings_button->setHidden(true);
          search_widget->expand();
        }
    });
  connect(search_widget, &SearchWidget::shrinked, [this](){
      settings_button->setHidden(false);
    });

  main_Layout = new QHBoxLayout(this);
  main_Layout->setContentsMargins(0,0,10,0);
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

void SearchBar::enterEvent(QEvent *e)
{
  if(search_focus_lock || settings_toggled)
    return;
  search_widget->shrink();
  QWidget::enterEvent(e);
}

void SearchBar::leaveEvent(QEvent *e)
{
  if(search_focus_lock || settings_toggled)
    return;
  settings_button->setHidden(true);
  search_widget->expand();
  QWidget::leaveEvent(e);
}






