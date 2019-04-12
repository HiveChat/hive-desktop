#include "Button.h"

#include <QGraphicsDropShadowEffect>
#include <QFontMetrics>
#include <QFrame>
#include <QPainter>
#include <QStaticText>

/*
 * Try to use:
 *  qreal dpr = App::app()->devicePixelRatio();
 * To get suitable pixel ratio in different devices
 *
 */

LabelButton::LabelButton(const int &hoverDelay, QWidget *parent)
  : QLabel(parent)
  , hover_delay(hoverDelay)
{
}

void LabelButton::setDefaultPixmap(const QString &path)
{
  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(Global::window_dpr);
  this->setPixmap(default_pixmap);
}

void LabelButton::setHoveredPixmap(const QString &path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(Global::window_dpr);
}

void LabelButton::setPressedPixmap(const QString &path)
{
  pressed_pixmap.load(path);
  pressed_pixmap.setDevicePixelRatio(Global::window_dpr);
}

void LabelButton::setDefault()
{
  if(!disabled)
    {
      this->setPixmap(default_pixmap);
    }
}

void LabelButton::setHovered()
{
  if(!disabled)
    {
      this->setPixmap(hovered_pixmap);
    }
}


////////////events
void LabelButton::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      if(!pressed_pixmap.isNull())
        {
          this->setPixmap(pressed_pixmap);
        }
    }

}

void LabelButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      //this->setPixmap(default_pixmap);
      emit clicked();
    }
}

void LabelButton::enterEvent(QEvent *)
{
  setHovered();
  if(hover_delay != 0)
    {
      hover_signal_lock = false;
      QTimer::singleShot(hover_delay, [this]() {
          if(!hover_signal_lock)
            emit entered();
          else
            hover_signal_lock = false;
        });
    }
  else
    {
      emit entered();
    }
}

void LabelButton::leaveEvent(QEvent *)
{
  setDefault();
  if(hover_delay != 0)
    {
      if(!hover_signal_lock)
        {
          emit left();
          hover_signal_lock = true;
        }
    }
  else
    {
      emit left();
    }
}





MenuButton::MenuButton(QString text, GUI::StaticStackType staticStackType, QWidget *parent)
  : QWidget(parent)
{
  static_stack_type = staticStackType;

  icon_label = new QLabel(this);

  text_label = new QLabel(this);
  text_label->setText(text);
  text_label->setFont(Global::font_menuButton);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->addWidget(icon_label);
  main_layout->addWidget(text_label);

  text_palette.setColor(QPalette::WindowText, default_text_color);

  this->setPalette(text_palette);
  this->setLayout(main_layout);
}

MenuButton::~MenuButton()
{

}

void MenuButton::setDefaultPixmap(QString path)
{
  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(Global::window_dpr);
  setDefault();
}

void MenuButton::setHoveredPixmap(QString path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(Global::window_dpr);
}




void MenuButton::mousePressEvent(QMouseEvent *)
{
  emit clicked(static_stack_type);
}

void MenuButton::mouseReleaseEvent(QMouseEvent *)
{

}

void MenuButton::enterEvent(QEvent *)
{
  setHovered();
}

void MenuButton::leaveEvent(QEvent *)
{
  setDefault();
}

void MenuButton::setDefault()
{
  text_palette.setColor(QPalette::WindowText, default_text_color);
  text_label->setPalette(text_palette);
  icon_label->setPixmap(default_pixmap);
}

void MenuButton::setHovered()
{
  text_palette.setColor(QPalette::WindowText, hovered_text_color);
  text_label->setPalette(text_palette);
  icon_label->setPixmap(hovered_pixmap);
}






FloatButton::FloatButton(const QString &txt, QWidget *parent, const QColor &color)
  : QFrame(parent)
  , text_(txt)
  , color_(color)
{
  //  font_.setFamily("Gill Sans Light");
  font_.setPixelSize(13);

  QFontMetrics fm(font_);
  width_ = static_cast<int>(fm.width(txt) + fm.height() * 2.5);
  height_ = static_cast<int>(fm.height() * 1.8);
  radius_ = height_ / 2;

  text_option_.setAlignment(Qt::AlignCenter);
  text_option_.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

  QGraphicsDropShadowEffect *e = new QGraphicsDropShadowEffect(this);
  e->setBlurRadius(radius_*3);
  e->setXOffset(0);
  e->setYOffset(0);
  e->setColor(color_.lighter(105));

  this->setGraphicsEffect(e);
  this->setFixedSize(QSize(width_,height_));
  this->setAutoFillBackground(true);
  this->setStyleSheet("border-radius: 10px;");
}

void FloatButton::paintEvent(QPaintEvent *)
{
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(hovered_ ? color_.lighter(110) : color_,Qt::SolidPattern));
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawRoundedRect(QRect(1, 1, width_ - 1, height_ - 1), radius_, radius_);
  painter.setFont(font_);
  painter.setPen(hovered_ ? QColor(250, 250, 250) : QColor(255, 255, 255));
  painter.drawText(this->rect(), text_, text_option_);
  painter.end();
}

void FloatButton::mousePressEvent(QMouseEvent *)
{

}

void FloatButton::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked();
}

void FloatButton::enterEvent(QEvent *)
{
  hovered_ = true;
  this->update();
}

void FloatButton::leaveEvent(QEvent *)
{
  hovered_ = false;
  this->update();
}



