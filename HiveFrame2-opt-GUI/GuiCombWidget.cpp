#include "GuiCombWidget.h"

GuiCombWidget::GuiCombWidget(QString avatarPath, QString usrName, QString ipAddr, QWidget *parent) : QWidget(parent)
{
  avatar = new GuiAvatarButton(avatarPath, 80, 0, this);
  usr_name_label = new QLabel(usrName);
  ip_addr_label = new QLabel(ipAddr);
  status_label = new QLabel("·");

  QPalette usr_name_palette;
  usr_name_palette.setColor(QPalette::WindowText, QColor(103,72,0));
  QFont usr_name_font("Verdana");
  usr_name_font.setPixelSize(15);
  usr_name_label->setPalette(usr_name_palette);
  usr_name_label->setFont(usr_name_font);

  QFont ip_addr_font("Gill Sans");
  ip_addr_font.setPixelSize(11);
  ip_addr_label->setFont(ip_addr_font);

  ip_status_layout = new QHBoxLayout();
  ip_status_layout->addWidget(status_label);
  ip_status_layout->addWidget(ip_addr_label);

  usr_info_layout = new QVBoxLayout();
  usr_info_layout->setSpacing(0);
  usr_info_layout->addWidget(usr_name_label);
  usr_info_layout->addLayout(ip_status_layout);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->addWidget(avatar);
  main_layout->addLayout(usr_info_layout);

}

GuiCombWidget::~GuiCombWidget()
{

}


void GuiCombWidget::mouseReleaseEvent(QMouseEvent *)
{
  selected != selected;
}

void GuiCombWidget::enterEvent(QEvent *)
{
  hovered = true;
}

void GuiCombWidget::leaveEvent(QEvent *)
{
  hovered = false;
}

