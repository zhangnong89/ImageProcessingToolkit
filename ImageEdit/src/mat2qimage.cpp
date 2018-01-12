#include"mat2qimage.h"

QImage Mat2QImage(cv::Mat const& src)
{
  QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

  const float scale = 255.0;

  if (src.depth() == CV_8U) {
    if (src.channels() == 1) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          int level = src.at<quint8>(i, j);
          dest.setPixel(j, i, qRgb(level, level, level));
        }
      }
    } else if (src.channels() == 3) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
          dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
        }
      }
    }
  } else if (src.depth() == CV_32F) {
    if (src.channels() == 1) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          int level = scale * src.at<float>(i, j);
          dest.setPixel(j, i, qRgb(level, level, level));
        }
      }
    } else if (src.channels() == 3) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
          dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
        }
      }
    }
  }

  return dest;
}









#if 1
    QImage *IplImageToQImage(const IplImage *img)
    {
        QImage *image;
        cvCvtColor((CvArr*)img,(CvArr*)img,CV_BGR2RGB);
        uchar *imgData=(uchar *)img->imageData;
        image=new QImage(imgData,img->width,img->height,QImage::Format_RGB888);
        return image;
    }

    IplImage *QImageToIplImage(const QImage * qImage)
    {
        int width = qImage->width();
        int height = qImage->height();
        CvSize Size;
        Size.height = height;
        Size.width = width;
        IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                QRgb rgb = qImage->pixel(x, y);
                cvSet2D(IplImageBuffer, y, x, CV_RGB(qRed(rgb), qGreen(rgb), qBlue(rgb)));
            }
        }
        return IplImageBuffer;
    }
#endif
