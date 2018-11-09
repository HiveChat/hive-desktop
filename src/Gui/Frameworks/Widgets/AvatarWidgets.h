#ifndef GUIAVATARBUTTON_H
#define GUIAVATARBUTTON_H

#include "Global.h"

#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>

#include <QSlider>
#include <QScrollBar>
#include <QDial>
#include <QLabel>
#include <QGridLayout>

#include <QPainter>
#include <QBitmap>

#include <QDebug>



class AvatarButton : public QLabel
{
  Q_OBJECT

public:
  AvatarButton(const int &Diameter, QWidget *parent = nullptr);
  AvatarButton(const QString &path, const int &Diameter, QWidget *parent = nullptr);

  void setAvatar(const QString &path);

protected:
  void mouseReleaseEvent(QMouseEvent *);

private:
  int diameter;

signals:
  void clicked();
};




class AvatarComposer : public QWidget
{
  Q_OBJECT

public:
  AvatarComposer(const QSize &size, QWidget *parent = nullptr);
  ~AvatarComposer();

  void setSourceImage(const QString &path);

protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void wheelEvent(QWheelEvent *event);

private:
  void render();
  void highQualityRender();

  QLabel *result_label;
  QSlider *horinzontal_slider;
  QSlider *vertical_slider;
  QSlider *scale_slider;

  QImage image;
  QImage scaled_source_image;
  QImage mask;
  QImage rendered_image;

  QSize scaled_source_size;
  QSize result_avatar_size;

  QString image_path;

  bool render_lock = true;
  bool high_quality_rendering = false;
};

#endif // GUIAVATARBUTTON_H
