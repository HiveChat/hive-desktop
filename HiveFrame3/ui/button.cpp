#include "button.h"

Button::Button(const QString &txt, int w, int h, QWidget *parent)
  : QOpenGLWidget(parent)
  , width(w)
  , height(h)
  , text(txt)
{
  setFont("Gill Sans Light", 14);
  setText(txt);
  this->setFixedSize(QSize(w,h));
  this->setAutoFillBackground(false);
}

Button::Button(const QString &txt, QWidget *parent)
  : QOpenGLWidget(parent)
{
  setFont("Gill Sans Light", 13);
  setText(txt);
  this->setMinimumSize(QSize(width, height));
  this->setAutoFillBackground(false);
}

void Button::setFont(const QFont &f)
{
  font = f;
  updateTextRect();

}

void Button::setFont(const QString &family, const int &pixelSize)
{
  font.setFamily(family);
  font.setPixelSize(14);
  updateTextRect();
}

void Button::setText(const QString &str)
{
  text = str;
  updateTextRect();
}

void Button::setPalette(const Button::Palette &palette, const QColor &color)
{
  switch (palette) {
    case Palette::BackgroundDefault:
      {
        background_default_color = color;
        break;
      }
    case Palette::BackgroundHovered:
      {
        background_hovered_color = color;
        break;
      }
      break;
    case Palette::ForegroundDefault:
      {
        foreground_default_color = color;
        break;
      }
      break;
    case Palette::ForegroundHovered:
      {
        foreground_hovered_color = color;
        break;
      }
    default:
      break;
    }
}

void Button::paintEvent(QPaintEvent *)
{
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(hovered ? background_hovered_color :background_default_color, Qt::SolidPattern));
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawRoundedRect(background_rect,5,5);
  QTextOption textOption;
  textOption.setAlignment(Qt::AlignCenter);
  textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
  painter.setFont(font);
  painter.setPen(hovered ? foreground_hovered_color : foreground_default_color);
  painter.drawText(this->rect(), text, textOption);
  if (painter.paintEngine()->type() != QPaintEngine::OpenGL2) {
          qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
          qDebug()<<painter.paintEngine()->type();
          return;
      }
  painter.end();
}

void Button::resizeEvent(QResizeEvent *ev)
{
  background_rect = QRect(1, (this->rect().height() - height) * 0.5 + 1, this->rect().width() - 1, height - 1);
  QOpenGLWidget::resizeEvent(ev);
}

void Button::mousePressEvent(QMouseEvent *)
{

}

void Button::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked();
}

void Button::enterEvent(QEvent *ev)
{
  hovered = true;
  this->update();
}

void Button::leaveEvent(QEvent *ev)
{
  hovered = false;
  this->update();
}

void Button::updateTextRect()
{
  QFontMetrics metrics(font);
  width = metrics.width(text) + 40;
  update();
}


