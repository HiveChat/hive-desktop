#include "mainwindow.h"
#include <QDebug>
#include <QBitmap>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  gui_central_widget = new GuiCentralWidget(this);
  connect(gui_central_widget->gui_tab_block->exit_hint, SIGNAL(clicked()), this, SLOT(close()));
  connect(gui_central_widget->gui_tab_block->min_hint, SIGNAL(clicked()), this, SLOT(showMinimized()));
  connect(gui_central_widget->gui_tab_block->max_hint, SIGNAL(clicked()), this, SLOT(setWindowMaximized()));

  //this->setWindowIcon(QIcon(":/img/img/icon.png"));
  this->setMinimumHeight(500);
  this->setMinimumWidth(800);
  this->setCentralWidget(gui_central_widget);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowFlags(Qt::FramelessWindowHint);
  this->setWindowState(Qt::WindowNoState);
  //this->setWindowFlags(Qt::CustomizeWindowHint);


}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent*)
{
  ///rounded frame     //scroll bug here!
  QBitmap bmp(this->size());
  bmp.setDevicePixelRatio(1.0);
  bmp.fill();
  QPainter p(&bmp);
  p.setPen(Qt::NoPen);
  p.setBrush(Qt::black);
  p.setRenderHint(QPainter::Antialiasing, true);
  p.drawRoundedRect(bmp.rect(), 10, 10);
  this->setMask(bmp);

  ///color
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.fillRect(rect(), QColor(255,204,0,255));
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
 if(event->button() == Qt::LeftButton)
 {
      mouse_press = true;
      //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
      move_point = event->pos();;
 }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();

       //移动主窗体位置
       this->move(move_pos - move_point);
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    mouse_press = false;
}

void MainWindow::setWindowMaximized()
{
  if(maximized)
    {
      setWindowState(Qt::WindowNoState);
      maximized = false;
    }
  else
    {
      setWindowState(Qt::WindowFullScreen);
      maximized = true;
    }
}


