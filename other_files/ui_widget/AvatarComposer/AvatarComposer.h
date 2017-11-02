#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QDial>
#include <QDragEnterEvent>
#include <QMimeData>

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

#endif // WIDGET_H
