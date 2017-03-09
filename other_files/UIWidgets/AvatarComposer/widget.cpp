#include "widget.h"

Widget::Widget(const QSize &size, QWidget *parent)
  : QWidget(parent)
  , image_size(size)
{
  destination_image = QImage(image_size, QImage::Format_ARGB32_Premultiplied);
  QPainter painter(&destination_image);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(destination_image.rect(), QBrush(Qt::black, Qt::SolidPattern));
  painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::transparent, Qt::SolidPattern));
  painter.drawEllipse(destination_image.rect());

  result_image = QImage(image_size, QImage::Format_ARGB32_Premultiplied);

  result_label = new QLabel("drag avatar here!", this);
  horinzontal_slider = new QSlider(this);
  horinzontal_slider->setOrientation(Qt::Horizontal);
  horinzontal_slider->setRange(0, 99);
  vertical_slider = new QSlider(this);
  vertical_slider->setOrientation(Qt::Vertical);
  vertical_slider->setRange(0, 99);
  scale_dial = new QDial(this);
  scale_dial->setRange(100, 200);

  QGridLayout *grid_layout = new QGridLayout();
  grid_layout->addWidget(result_label, 0, 0, 3, 3, Qt::AlignCenter);
  grid_layout->addWidget(vertical_slider, 1, 2, 1, 5, Qt::AlignCenter);
  grid_layout->addWidget(horinzontal_slider, 2, 1, 5, 1, Qt::AlignCenter);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->addWidget(scale_dial);
  main_layout->addLayout(grid_layout);

  connect(horinzontal_slider, &QSlider::valueChanged, this, &Widget::render);
  connect(vertical_slider, &QSlider::valueChanged, this, &Widget::render);
  connect(scale_dial, &QDial::valueChanged, this, &Widget::render);

  setSourceImage("/Users/echo/Desktop/IMG_20170208_134046.jpg");
  render();
}

Widget::~Widget()
{

}

void Widget::setSourceImage(const QString &fileName)
{
  source_image.load(fileName);
  QPixmap sourcePixmap = QPixmap::fromImage(source_image.scaled(image_size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
  sourcePixmap.setDevicePixelRatio(2.0);


}

void Widget::render()
{
  QPainter painter(&result_image);
  painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.fillRect(result_image.rect(), Qt::transparent);
  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
  painter.drawImage(0, 0, destination_image);
  painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
  QImage img = source_image.scaled(QSize(image_size.width() * scale_dial->value()/100, image_size.height() * scale_dial->value()/100), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  painter.drawImage(- img.width()/100*horinzontal_slider->value()
                    , - img.height()/100*vertical_slider->value()
                    , img);
  painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
  painter.fillRect(result_image.rect(), Qt::transparent);
  painter.end();

  QPixmap pixmap = QPixmap::fromImage(result_image);
  pixmap.setDevicePixelRatio(2.0);
  result_label->setPixmap(pixmap);
}
