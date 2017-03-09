#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QDial>

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(const QSize &size, QWidget *parent = 0);
  ~Widget();

  void setSourceImage(const QString &fileName);

private:
  QLabel *result_label;
  QSlider *horinzontal_slider;
  QSlider *vertical_slider;
  QDial *scale_dial;

  QImage source_image;
  QImage destination_image;
  QImage result_image;

  QSize image_size;

private slots:
  void render();

};

#endif // WIDGET_H
