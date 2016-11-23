#include "MenuButton.h"

MenuButton::MenuButton(QString text, GUI::StaticStackType staticStackType, QWidget *parent) : QWidget(parent)
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

MenuButton::~MenuButton()
{

}

void MenuButton::setDefaultPixmap(QString path)
{
  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(2.0);
  setDefault();
}

void MenuButton::setHoveredPixmap(QString path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(2.0);
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

