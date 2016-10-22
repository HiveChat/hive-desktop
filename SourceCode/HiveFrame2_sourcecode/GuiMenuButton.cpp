#include "GuiMenuButton.h"

GuiMenuButton::GuiMenuButton(QString text, StaticStackType staticStackType, QWidget *parent) : QWidget(parent)
{
  static_stack_type = staticStackType;

  icon_label = new QLabel(this);

  text_label = new QLabel(this);
  text_label->setText(text);
  text_label->setFont(GlobalData::font_menuButton);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->addWidget(icon_label);
  main_layout->addWidget(text_label);

  text_palette.setColor(QPalette::WindowText, default_text_color);

  this->setPalette(text_palette);
  this->setLayout(main_layout);
  this->setParent(parent);
}

GuiMenuButton::~GuiMenuButton()
{

}

void GuiMenuButton::setDefaultPixmap(QString path)
{
  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(2.0);
  setDefault();
}

void GuiMenuButton::setHoveredPixmap(QString path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(2.0);
}




void GuiMenuButton::mousePressEvent(QMouseEvent *)
{
  emit clicked(static_stack_type);
}

void GuiMenuButton::mouseReleaseEvent(QMouseEvent *)
{

}

void GuiMenuButton::enterEvent(QEvent *)
{
  setHovered();
}

void GuiMenuButton::leaveEvent(QEvent *)
{
  setDefault();
}

void GuiMenuButton::setDefault()
{
  text_palette.setColor(QPalette::WindowText, default_text_color);
  text_label->setPalette(text_palette);
  icon_label->setPixmap(default_pixmap);
}

void GuiMenuButton::setHovered()
{
  text_palette.setColor(QPalette::WindowText, hovered_text_color);
  text_label->setPalette(text_palette);
  icon_label->setPixmap(hovered_pixmap);
}

