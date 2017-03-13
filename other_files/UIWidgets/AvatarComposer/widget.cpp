#include "widget.h"
#include <QDebug>

AvatarComposer::AvatarComposer(const QSize &size, QWidget *parent)
  : QWidget(parent)
  , result_avatar_size(size)
{
  result_image = QImage(result_avatar_size, QImage::Format_ARGB32_Premultiplied);
  destination_image = QImage(result_avatar_size, QImage::Format_ARGB32_Premultiplied);
  QPainter painter(&destination_image);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(destination_image.rect(), QBrush(Qt::black, Qt::SolidPattern));
  painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::transparent, Qt::SolidPattern));
  painter.drawEllipse(destination_image.rect());


  result_label = new QLabel("drag avatar here!", this);
  horinzontal_slider = new QSlider(this);
  horinzontal_slider->setOrientation(Qt::Horizontal);
  horinzontal_slider->setLayoutDirection(Qt::RightToLeft);
  vertical_slider = new QSlider(this);
  vertical_slider->setOrientation(Qt::Vertical);
  scale_slider = new QSlider(this);
  scale_slider->setTickPosition(QSlider::TicksRight);
  scale_slider->setRange(100, 200);

  QGridLayout *grid_layout = new QGridLayout();
  grid_layout->addWidget(result_label, 0, 0, 3, 3, Qt::AlignCenter);
  grid_layout->addWidget(vertical_slider, 1, 2, 1, 5, Qt::AlignCenter);
  grid_layout->addWidget(horinzontal_slider, 2, 1, 5, 1, Qt::AlignCenter);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->addWidget(scale_slider);
  main_layout->addSpacing(30);
  main_layout->addLayout(grid_layout);

  connect(horinzontal_slider, &QSlider::valueChanged, this, &AvatarComposer::render);
  connect(vertical_slider, &QSlider::valueChanged, this, &AvatarComposer::render);
  connect(scale_slider, &QDial::valueChanged, this, &AvatarComposer::render);
  connect(scale_slider, &QDial::sliderReleased, this, &AvatarComposer::onScaleSliderReleased);

  setSourceImage("/Users/echo/Desktop/IMG_20170208_134046.jpg");
  render();
}

AvatarComposer::~AvatarComposer()
{

}

void AvatarComposer::setSourceImage(const QString &fileName)
{
  source_image.load(fileName);
  scaled_source_size = source_image.size().scaled(result_avatar_size, Qt::KeepAspectRatioByExpanding);
  scaled_source_image = source_image.scaled(scaled_source_size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  horinzontal_slider->setRange(0, scaled_source_size.width() - result_avatar_size.width());
  vertical_slider->setRange(0, scaled_source_size.height() - result_avatar_size.height());
}

void AvatarComposer::render()
{
  if(render_lock)
    {
      return;
    }
  else
    {
      render_lock = true;
    }

  QPainter painter(&result_image);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.fillRect(result_image.rect(), Qt::transparent);
  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
  painter.drawImage(0, 0, destination_image);
  painter.setCompositionMode(QPainter::CompositionMode_SourceOut);

//  qDebug()<<"original: "<<source_image.size();

  if(sender() == scale_slider)
    {
      scaled_source_size = QSize(result_avatar_size.width() * scale_slider->value() * 0.01
                                 , result_avatar_size.height() * scale_slider->value() * 0.01);

      if(scale_slider_released)
        {
          scaled_source_image = source_image.scaled(scaled_source_size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        }
      else
        {
          scaled_source_image = source_image.scaled(scaled_source_size, Qt::KeepAspectRatioByExpanding, Qt::FastTransformation);
        }
      horinzontal_slider->setRange(0, scaled_source_image.width() - result_avatar_size.width());
      vertical_slider->setRange(0, scaled_source_image.height() - result_avatar_size.height());
    }

  painter.drawImage(- horinzontal_slider->value()
                    , - vertical_slider->value()
                    , scaled_source_image);
  painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
  painter.fillRect(result_image.rect(), Qt::transparent);
  painter.end();


  QPixmap pixmap = QPixmap::fromImage(result_image);
  pixmap.setDevicePixelRatio(2.0);
  result_label->setPixmap(pixmap);

  render_lock = false;
}

void AvatarComposer::onScaleSliderReleased()
{
  scale_slider_released = true;
  render();
  scale_slider_released = false;
}
