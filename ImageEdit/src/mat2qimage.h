#ifndef MAT2QIMAGE
#define MAT2QIMAGE

#include"all.h"

namespace cv {
class Mat;
}

QImage Mat2QImage(cv::Mat const&);


QImage *IplImageToQImage(const IplImage *img);
IplImage *QImageToIplImage(const QImage * qImage);

#endif // MAT2QIMAGE

