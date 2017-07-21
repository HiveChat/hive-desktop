#include "_showcase.h"

_Showcase::_Showcase(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  bt1 = new Button("cancel", this);
  bt1->setPalette(Button::ForegroundHovered, QColor("#f7a527"));
  bt1->setPalette(Button::BackgroundHovered, QColor("#ffffff"));

  bt2 = new Button("invite", this);
  bt2->setPalette(Button::ForegroundDefault, QColor("#f7a527"));
  bt2->setPalette(Button::ForegroundHovered, QColor("#f7a527"));
  bt2->setPalette(Button::BackgroundHovered, QColor("#f9f2d2"));

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  mainLayout->addWidget(bt1);
  mainLayout->addWidget(bt2);


//  screenshot_mat = qImage2cvMat(this->grab(this->rect()).toImage());

//  cvSmooth(screenshot_mat,newimage,CV_BLUR,3,3,0,0);
//  cvNamedWindow("WINDOWNAME1");
//  cvShowImage("WINDOWNAME1", screenshot_mat);

}

_Showcase::~_Showcase()
{
  qDebug()<<"f";
  bt1->deleteLater();
  bt2->deleteLater();
  qDebug()<<"\f";

}

//QImage _Showcase::cvMat2QImage(const cv::Mat& mat)
//{
//    // 8-bits unsigned, NO. OF CHANNELS = 1
//    if(mat.type() == CV_8UC1)
//    {
//        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
//        // Set the color table (used to translate colour indexes to qRgb values)
//        image.setColorCount(256);
//        for(int i = 0; i < 256; i++)
//        {
//            image.setColor(i, qRgb(i, i, i));
//        }
//        // Copy input Mat
//        uchar *pSrc = mat.data;
//        for(int row = 0; row < mat.rows; row ++)
//        {
//            uchar *pDest = image.scanLine(row);
//            memcpy(pDest, pSrc, mat.cols);
//            pSrc += mat.step;
//        }
//        return image;
//    }
//    // 8-bits unsigned, NO. OF CHANNELS = 3
//    else if(mat.type() == CV_8UC3)
//    {
//        // Copy input Mat
//        const uchar *pSrc = (const uchar*)mat.data;
//        // Create QImage with same dimensions as input Mat
//        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
//        return image.rgbSwapped();
//    }
//    else if(mat.type() == CV_8UC4)
//    {
//        qDebug() << "CV_8UC4";
//        // Copy input Mat
//        const uchar *pSrc = (const uchar*)mat.data;
//        // Create QImage with same dimensions as input Mat
//        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
//        return image.copy();
//    }
//    else
//    {
//        qDebug() << "ERROR: Mat could not be converted to QImage.";
//        return QImage();
//    }
//}

//cv::Mat _Showcase::qImage2cvMat(QImage image)
//{
//    cv::Mat mat;
//    switch(image.format())
//    {
//    case QImage::Format_ARGB32:
//    case QImage::Format_RGB32:
//    case QImage::Format_ARGB32_Premultiplied:
//        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
//        break;
//    case QImage::Format_RGB888:
//        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//        break;
//    case QImage::Format_Indexed8:
//        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.bits(), image.bytesPerLine());
//        break;
//    }
//    return mat;
//}
