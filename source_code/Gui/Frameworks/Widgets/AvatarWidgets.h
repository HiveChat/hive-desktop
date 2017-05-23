#ifndef GUIAVATARBUTTON_H
#define GUIAVATARBUTTON_H

#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>

#include <QSlider>
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
  AvatarButton(const QString path, const int Diameter, QWidget *parent);
  AvatarButton(const int Diameter, QWidget *parent);

  void setAvatar(const QString &path);

protected:
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  int diameter;

signals:
  void clicked();

};




class AvatarComposer : public QWidget
{
  Q_OBJECT

public:
  AvatarComposer(const QSize &size, QWidget *parent = 0);
  ~AvatarComposer();

  void setSourceImage(const QString &fileName);

protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void wheelEvent(QWheelEvent *event);

private:
  QLabel *result_label;
  QSlider *horinzontal_slider;
  QSlider *vertical_slider;
  QSlider *scale_slider;

  QImage source_image;
  QImage scaled_source_image;
  QImage destination_image;
  QImage result_image;

  QSize scaled_source_size;
  QSize result_avatar_size;

  QString source_image_name;

  bool render_lock = true;
  bool high_quality_rendering = false;

private slots:
  void render();
  void highQualityRender();

};

#endif // GUIAVATARBUTTON_H
