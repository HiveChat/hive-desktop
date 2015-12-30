#include "GuiCombWidget.h"
#include <QDebug>


GuiCombWidget::GuiCombWidget(QStringList usrInfoStrList, QWidget *parent) : QWidget(parent)
{
  usr_info_str_list = usrInfoStrList;
  ///macAddr<<usrName<<ipAddr
  avatar = new GuiAvatarButton("/Users/Echo/Desktop/zLjJv8.png.jpeg", 80, 0, this);
  usr_name_label = new QLabel(usrInfoStrList[1]);
  ip_addr_label = new QLabel(usrInfoStrList[2]);
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

  hover_palette.setColor(QPalette::Window, default_window_color);

  this->setMinimumWidth(200);
  this->setPalette(hover_palette);
  this->setAutoFillBackground(true);

}

GuiCombWidget::~GuiCombWidget()
{

}

QStringList GuiCombWidget::usrInfo()
{
  return usr_info_str_list;
}


//////events

void GuiCombWidget::paintEvent(QPaintEvent *)
{
  QRectF rectangle(0, 0, this->width(), this->height());
  QPainter paint;
  paint.begin(this);
  paint.setPen(QPen(Qt::NoPen));
  paint.setBrush(QBrush(window_color,Qt::SolidPattern));

  paint.drawRoundedRect(rectangle,5,5);
  paint.end();
}

void GuiCombWidget::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked();
}

void GuiCombWidget::enterEvent(QEvent *)
{
  window_color = hovered_window_color;
  repaint();
  hovered = true;
}

void GuiCombWidget::leaveEvent(QEvent *)
{
  window_color = default_window_color;
  repaint();
  hovered = false;
}


