#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QDial>

class AvatarComposer : public QWidget
{
  Q_OBJECT

public:
  AvatarComposer(const QSize &size, QWidget *parent = 0);
  ~AvatarComposer();

  void setSourceImage(const QString &fileName);

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

  bool render_lock;
  bool scale_slider_released;
private slots:
  void render();
  void onScaleSliderReleased();

};

#endif // WIDGET_H
