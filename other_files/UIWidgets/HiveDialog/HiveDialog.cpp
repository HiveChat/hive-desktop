#include "HiveDialog.h"

HiveDialog::HiveDialog(QString title, QString content, QSize size, QWidget *parent)
  : QWidget(parent)
{
  ////window btn
  exit_hint = new GuiLabelButton(this);
  min_hint = new GuiLabelButton(this);
  max_hint = new GuiLabelButton(this);

  exit_hint->setDefaultPixmap(":/img/img/exit_hint_0.png");
  exit_hint->setHoveredPixmap(":/img/img/exit_hint_1.png");

  min_hint->setDefaultPixmap(":/img/img/min_hint_0.png");
  min_hint->setHoveredPixmap(":/img/img/min_hint_1.png");

  max_hint->setDefaultPixmap(":/img/img/max_hint_0.png");
  max_hint->setHoveredPixmap(":/img/img/max_hint_1.png");

  connect(exit_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
  connect(exit_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));
  connect(min_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
  connect(min_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));
  connect(max_hint, SIGNAL(entered()), this, SLOT(changeWindowBtn()));
  connect(max_hint, SIGNAL(left()), this, SLOT(recoverWindowBtn()));

  connect(exit_hint, SIGNAL(clicked()), this, SLOT(deleteLater()));
  connect(min_hint, SIGNAL(clicked()), this, SLOT(showMinimized()));
  connect(max_hint, SIGNAL(clicked()), this, SLOT(setWindowMaximized()));


  ////window btn layout
  window_btn_layout = new QHBoxLayout(this);
  window_btn_layout->setMargin(10);
  window_btn_layout->setSpacing(8);
  window_btn_layout->setSizeConstraint(QLayout::SetFixedSize);
  window_btn_layout->setAlignment(Qt::AlignLeft | Qt ::AlignTop);
  window_btn_layout->addWidget(exit_hint);
  window_btn_layout->addWidget(min_hint);
  window_btn_layout->addWidget(max_hint);



  this->setMinimumSize(300,150);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowFlags(Qt::FramelessWindowHint);

}

HiveDialog::~HiveDialog()
{

}

void HiveDialog::paintEvent(QPaintEvent*)
{
  ///rounded frame     //scroll bug here!
//  QBitmap bmp(this->size());
//  bmp.fill();
//  QPainter p(&bmp);
//  p.setPen(Qt::NoPen);
//  p.setBrush(Qt::black);
//  p.setRenderHint(QPainter::Antialiasing, true);
//  p.setRenderHint(QPainter::SmoothPixmapTransform);
//  p.drawRoundedRect(bmp.rect(), 8, 8);
//  bmp.setDevicePixelRatio(2.0);
//  this->setMask(bmp);

//  ///color
//  QPainter painter(this);
//  painter.setRenderHint(QPainter::Antialiasing, true);
//  painter.fillRect(rect(), QColor(255,255,255,255));

  QRectF rectangle(0, 0, this->width(), this->height());
  QPainter paint(this);
  paint.setPen(QPen(Qt::NoPen));
  paint.setBrush(QBrush(QColor(254,232,114),Qt::SolidPattern));
  paint.drawRoundedRect(rectangle,5,5);
}

void HiveDialog::changeWindowBtn()
{
  exit_hint->setHovered();
  min_hint->setHovered();
  max_hint->setHovered();
}

void HiveDialog::recoverWindowBtn()
{
  exit_hint->setDefault();
  min_hint->setDefault();
  max_hint->setDefault();
}

void HiveDialog::mousePressEvent(QMouseEvent *event)
{
  ///drag area!
  if(event->button() == Qt::LeftButton && event->pos().y() <= 35)
    {
      mouse_pressed = true;
      //mouse position to the main window the same as: event->globalPos() - this->pos()
      move_point = event->pos();
    }
}
void HiveDialog::mouseMoveEvent(QMouseEvent *event)
{
  if(mouse_pressed)
    {
      QPoint move_pos = event->globalPos();
      this->move(move_pos - move_point);
    }
}
void HiveDialog::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_pressed = false;
}

void HiveDialog::setWindowMaximized()
{
  if(maximized)
    {
      setWindowState(Qt::WindowNoState);
      maximized = false;
    }
  else
    {
      this->setWindowState(Qt::WindowFullScreen);
      maximized = true;
    }
}
