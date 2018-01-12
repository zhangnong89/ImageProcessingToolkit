#ifndef PICTUREMOSAIC
#define PICTUREMOSAIC
#include "all.h"
#include <QRect>
class PictureView;
class PictureMosaic : public QWidget
{

    Q_OBJECT

public:
    explicit PictureMosaic(QWidget *parent = 0);

//鼠标坐标在图片显示区域和图像缩放之后坐标的转换
    void pictureAndWidgetSize(PictureView*pictureView);
    void mouseDragBrush();
    void mouseDragEraser();
    QSizeF mousePointTransfer(QMouseEvent *event);
    void doMosaic(QSizeF, PictureView*, int, bool);
    void doEraser(QSizeF, PictureView*, int, bool);
    bool setRectFlag(QSizeF, int);
    ~PictureMosaic(void);

private:
    double imgOriginal_width;
    double imgOriginal_height;
    double imgCurrent_width;
    double imgCurrent_height;
    double widget_width;
    double widget_height;
    QLabel* brush;
    QLabel* eraser;
    cv::Mat tempImage;
    cv::Mat tmpImg;
    static cv::Mat beforeMosaicImage;

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void sig_drag(QMouseEvent*);
    void sig_mouseIsReleased();

};

#endif // PICTUREMOSAIC


