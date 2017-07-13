#ifndef _SHOWCASE_H
#define _SHOWCASE_H

#include "./ui/button.h"
#include <QHBoxLayout>
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class _Showcase : public QWidget
{
  Q_OBJECT
public:
  explicit _Showcase(QWidget *parent = nullptr);
  ~_Showcase();

signals:

public slots:

private:
  Button *bt1;
  Button *bt2;

  cv::Mat screenshot_mat;

//  cv::Mat qImage2cvMat(QImage screenshot_mat);
//  QImage cvMat2QImage(const cv::Mat& mat);
};

#endif // _SHOWCASE_H
