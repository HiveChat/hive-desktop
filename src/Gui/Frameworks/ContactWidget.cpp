#include "Gui/Frameworks/ContactWidget.h"
#include <QDebug>


ContactWidget::ContactWidget(UsrProfile *p, QWidget *parent)
  : QWidget(parent)
  , avatar(new AvatarButton(80,  this))
  , usr_name_label(new QLabel(this))
  , ip_addr_label(new QLabel(this))
  , status_label(new QLabel(this))
{
  hover_palette.setColor(QPalette::Window, default_window_color);
  this->setPalette(hover_palette);
  this->setMinimumWidth(200);
  this->setAutoFillBackground(true);
  this->setAcceptDrops(true);
  this->setToolTipDuration(1000);
  setProfile(p);

  QPalette usr_name_palette;
  usr_name_palette.setColor(QPalette::WindowText, QColor(64,64,64));

  usr_name_label->setPalette(usr_name_palette);
  usr_name_label->setFont(Global::font_contactWidgetUsrName);
  ip_addr_label->setFont(Global::font_contactWidgetIpAddr);
  status_label->setText(offline_dot);

  net_status_layout = new QHBoxLayout();
  net_status_layout->setAlignment(Qt::AlignLeft);
  net_status_layout->addWidget(status_label);
  net_status_layout->addWidget(ip_addr_label);

  usr_info_layout = new QVBoxLayout();
  usr_info_layout->setSpacing(0);
  usr_info_layout->addWidget(usr_name_label);
  usr_info_layout->addLayout(net_status_layout);

  badge_icon = new BadgeIcon(14, this);
  badge_icon->setNumber(18);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->addSpacing(10);
  main_layout->addWidget(avatar);
  main_layout->addLayout(usr_info_layout);
}

ContactWidget::~ContactWidget()
{

}

void ContactWidget::setProfile(UsrProfile *usrProfile)
{
  usr_profile = *usrProfile;

  avatar->setAvatar(usr_profile.avatar);
  usr_name_label->setText(usr_profile.name);
  ip_addr_label->setText(usr_profile.ip);

  if(usr_profile.ip.isEmpty() || usr_profile.ip == "Offline")
    {
      status_label->setText(offline_dot);
      this->setToolTip("offline");
    }
  else
    {
      if(getSubNetStr(Global::g_localHostIP) == getSubNetStr(usr_profile.ip))
        {
          status_label->setText(online_dot);
          this->setToolTip("online");
        }
      else
        {
          status_label->setText(unstable_dot);
          this->setToolTip("different subnet");
        }
    }

  return;
}

void ContactWidget::setBadgeNumber(const int &num)
{
  badge_icon->setNumber(num);
}


//void CombWidget::paintEvent(QPaintEvent *)
//{
//  QRectF rectangle(0, 0, this->width(), this->height());
//  QPainter painter;
//  painter.begin(this);
//  painter.setPen(QPen(Qt::NoPen));
//  painter.setBrush(QBrush(hovered ? hovered_window_color : default_window_color, Qt::SolidPattern));
//  painter.drawRoundedRect(rectangle,0,0);
//  painter.end();
//}

void ContactWidget::mouseReleaseEvent(QMouseEvent *)
{
  mousePressed = false;
  this->setHidden(false);
  emit clicked(usr_profile.key);
}

void ContactWidget::mousePressEvent(QMouseEvent *event)
{
  mousePressed = true;
  mouseEvent = event;

  if(event->button() == Qt::LeftButton)
    {
      QTimer::singleShot(100, [this](){
          if(mousePressed)
            {
              this->update();
              this->setHidden(true);
              QPixmap pixmap = grab(this->rect());//grab(this->rect());

              QByteArray itemData;
              QDataStream dataStream(&itemData, QIODevice::WriteOnly);
              dataStream << pixmap << QPoint(mouseEvent->pos() - this->pos());

              QMimeData *mimeData = new QMimeData();
              mimeData->setData("application/x-dnditemdata", itemData);

              QDrag *drag = new QDrag(this);
              drag->setMimeData(mimeData);
              drag->setPixmap(pixmap);
              drag->setHotSpot(QPoint(0,0));

              if(drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
                {
                  this->close();
                }
              else
                {
                  this->show();
                }
            }
        });
    }
}

void ContactWidget::enterEvent(QEvent *)
{
  hover_palette.setColor(QPalette::Window, hovered_window_color);
  this->setPalette(hover_palette);
}

void ContactWidget::leaveEvent(QEvent *)
{
  hover_palette.setColor(QPalette::Window, default_window_color);
  this->setPalette(hover_palette);
}

void ContactWidget::dragMoveEvent(QDragMoveEvent *)
{

}

QString ContactWidget::getSubNetStr(const QString &ipAddr)
{
  int loopNum = 0;
  QString subNetStr;

  for(int i = 0; i < ipAddr.size(); i++)
    {
      if(ipAddr.at(i) == '.')
          loopNum ++;

      if(loopNum == 3)
          break;

      if(loopNum == 2)
          subNetStr.append(ipAddr.at(i));
    }

  return subNetStr;
}

//void GuiCombWidget::dragMoveEvent(QEvent *)
//{

//}


