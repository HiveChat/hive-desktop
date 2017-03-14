#include "AvatarComposer.h"
#include <QDebug>

AvatarComposer::AvatarComposer(const QSize &size, QWidget *parent)
  : QWidget(parent)
  , result_avatar_size(size)
{
  //result_image is the final result
  result_image = QImage(result_avatar_size, QImage::Format_ARGB32_Premultiplied);
  //destination_image is the mask with a hole in the center
  destination_image = QImage(result_avatar_size, QImage::Format_ARGB32_Premultiplied);

  //Draw a transparent hole in a black square as avatar mask
  QPainter painter(&destination_image);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(destination_image.rect(), QBrush(Qt::black, Qt::SolidPattern));
  painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::transparent, Qt::SolidPattern));
  painter.drawEllipse(destination_image.rect());

  //GUI Widgets
  result_label = new QLabel("drag image here!", this);
  horinzontal_slider = new QSlider(this);
  horinzontal_slider->setOrientation(Qt::Horizontal);
  horinzontal_slider->setLayoutDirection(Qt::RightToLeft);
  vertical_slider = new QSlider(this);
  vertical_slider->setOrientation(Qt::Vertical);

  scale_slider = new QSlider(this);
  scale_slider->setTickPosition(QSlider::TicksRight);
  scale_slider->setRange(100, 250);
  QGridLayout *grid_layout = new QGridLayout();
  grid_layout->addWidget(result_label, 0, 0, 3, 3, Qt::AlignCenter);
  grid_layout->addWidget(vertical_slider, 1, 2, 1, 5, Qt::AlignCenter);
  grid_layout->addWidget(horinzontal_slider, 2, 1, 5, 1, Qt::AlignCenter);
  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->addWidget(scale_slider);
  main_layout->addSpacing(30);
  main_layout->addLayout(grid_layout);

  //High quality rendering (scaling) happens only when scale_slider is released, which minimizes CPU load.
  connect(horinzontal_slider, &QSlider::valueChanged, this, &AvatarComposer::render);
  connect(vertical_slider, &QSlider::valueChanged, this, &AvatarComposer::render);
  connect(scale_slider, &QDial::valueChanged, this, &AvatarComposer::render);
  connect(scale_slider, &QDial::sliderReleased, this, &AvatarComposer::highQualityRender);

//  setSourceImage("/Users/echo/Desktop/5123.png");

  this->setAcceptDrops(true);
}

AvatarComposer::~AvatarComposer()
{

}

void AvatarComposer::setSourceImage(const QString &fileName)
{
  //if already opened, return
  if(source_image_name == fileName)
    {
      return;
    }

  //load file
  if(!source_image.load(fileName))
    {
      return;
    }

  render_lock = false;
  source_image_name = fileName;
  scaled_source_size = source_image.size().scaled(result_avatar_size, Qt::KeepAspectRatioByExpanding);
  scaled_source_image = source_image.scaled(scaled_source_size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  scale_slider->setValue(100);
  horinzontal_slider->setValue(0);
  horinzontal_slider->setRange(0, scaled_source_size.width() - result_avatar_size.width());
  vertical_slider->setValue(0);
  vertical_slider->setRange(0, scaled_source_size.height() - result_avatar_size.height());

  highQualityRender();
}

void AvatarComposer::dragEnterEvent(QDragEnterEvent *event)
{
  event->accept();
}

void AvatarComposer::dropEvent(QDropEvent *event)
{
  QList<QUrl> urls = event->mimeData()->urls();
  if (urls.isEmpty())
    {
      return;
    }
  QString fileName = urls.first().toLocalFile();
  if (fileName.isEmpty())
    {
      return;
    }

  setSourceImage(fileName);
}

void AvatarComposer::wheelEvent(QWheelEvent *event)
 {
     QPoint numDegrees = event->angleDelta() * 0.125;
     scale_slider->setValue(scale_slider->value() + numDegrees.y());

     if(numDegrees.y() == 0)
       {
         high_quality_rendering = true;
       }
     event->accept();
 }

void AvatarComposer::render()
{
  //ensure that this function is finished before a second call
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

  if(sender() == scale_slider)
    {
      //calculate scale percentage
      float scaleFactor = scale_slider->value() * 0.01;
      scaled_source_size = QSize(result_avatar_size.width() * scaleFactor, result_avatar_size.height() * scaleFactor);
      scaled_source_image = source_image.scaled(scaled_source_size
                                                , Qt::KeepAspectRatioByExpanding
                                                , high_quality_rendering ? Qt::SmoothTransformation : Qt::FastTransformation);
      //reset range of slidebar after scaling
      horinzontal_slider->setRange(0, scaled_source_image.width() - result_avatar_size.width());
      vertical_slider->setRange(0, scaled_source_image.height() - result_avatar_size.height());
    }

  painter.drawImage(- horinzontal_slider->value(), - vertical_slider->value() , scaled_source_image);
  painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
  painter.fillRect(result_image.rect(), Qt::transparent);
  painter.end();

  QPixmap pixmap = QPixmap::fromImage(result_image);
  pixmap.setDevicePixelRatio(2.0);
  result_label->setPixmap(pixmap);

  render_lock = false;
  high_quality_rendering = false;
}

void AvatarComposer::highQualityRender()
{
  //I know, it's a crap, but works well
  high_quality_rendering = true;
  render();
  high_quality_rendering = false;
}

