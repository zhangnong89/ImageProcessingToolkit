#include "picturemosaic.h"
using namespace cv;
PictureMosaic::PictureMosaic(QWidget *parent)
    :QWidget(parent)
{

}

PictureMosaic::~PictureMosaic(void)
{

}

bool mosaicFlag = false;
Mat PictureMosaic::beforeMosaicImage;
//从PictureFilter中来
extern Mat noMosaicFilter;
extern bool filterFlag;

void PictureMosaic::pictureAndWidgetSize(PictureView* pictureView)
{
//载入图的原始尺寸
    imgOriginal_width = pictureView->imgOriginalWidth;
    imgOriginal_height = pictureView->imgOriginalHeight;
//载入图的当前尺寸
    imgCurrent_width = pictureView->imgCurrentWidth;
    imgCurrent_height = pictureView->imgCurrentHeight;
//显示图片de图片框的尺寸
    widget_width = this->parentWidget()->size().width();
    widget_height = this->parentWidget()->size().height();
    setWindowFlags(Qt::FramelessWindowHint);
    double x = 0;
    double y = 0;
    setGeometry(x, y, widget_width, widget_height);
}

void PictureMosaic::mouseDragBrush()
{
    brush = new QLabel(this);
    QGridLayout *layoutBrush = new QGridLayout(this);
    layoutBrush->addWidget(brush);
    layoutBrush->setMargin(0);
    setLayout(layoutBrush);
    brush->setMouseTracking(true);
//    brush->setCursor(Qt::CrossCursor);
    brush->setCursor(QPixmap(":/AdvancedImages/mosaic_brush_clicked.png"));
    this->show();
}
void PictureMosaic::mouseDragEraser()
{
    eraser = new QLabel(this);
    QGridLayout *layoutEraser = new QGridLayout(this);
    layoutEraser->addWidget(eraser);
    layoutEraser->setMargin(0);
    setLayout(layoutEraser);
    eraser->setMouseTracking(true);
//    eraser->setCursor(Qt::CrossCursor);
    eraser->setCursor(QPixmap(":/AdvancedImages/mosaic_eraser_clicked.png"));
    this->show();
}

void PictureMosaic::mouseMoveEvent(QMouseEvent * event)
{
        emit sig_drag(event);
}

void PictureMosaic::mouseReleaseEvent(QMouseEvent* event)
{
    emit sig_mouseIsReleased();
}

QSizeF PictureMosaic::mousePointTransfer(QMouseEvent *event)
{
    QSizeF rectSize;
//获得鼠标在widget空间的坐标
    int xx = event->pos().x();
    int yy = event->pos().y();
//offset
    double x_offset = widget_width - imgCurrent_width;
    double y_offset = widget_height - imgCurrent_height;
//将当前的图片像素坐标转化为原始图片的像素坐标
    double x = (xx-x_offset/2)*(imgOriginal_width/imgCurrent_width);
    double y = (yy-y_offset/2)*(imgOriginal_height/imgCurrent_height);
    rectSize = QSizeF(x, y);
    return rectSize;
}

//该函数的目的在于判断鼠标是否还在图片区域
bool PictureMosaic::setRectFlag(QSizeF rectSize, int mosaicWidthHeight)
{
    bool rectFlag;
    double x = rectSize.width();
    double y = rectSize.height();
    if(x>0&&x<imgOriginal_width-mosaicWidthHeight&&
            y>0&&y<imgOriginal_height-mosaicWidthHeight) rectFlag = true;
    else
        rectFlag = false;
    return rectFlag;
}

void PictureMosaic::doMosaic(QSizeF mosaicPoint, PictureView* pictureView,
                             int mosaicWidthHeight, bool rectFlag)
{
    if(rectFlag)
    {
        Mat Img_in ,sub_mat;
        pictureView->currentCvMat.copyTo(this->tempImage);
//判断上一步是否为马赛克刷
        if(mosaicFlag == false)
       {
           tempImage.copyTo(beforeMosaicImage);
       }
        mosaicFlag = true;
        double x = mosaicPoint.width();
        double y = mosaicPoint.height();
        Rect rect(x, y, mosaicWidthHeight, mosaicWidthHeight);
//设置感兴趣区域,拷贝
        tempImage(rect).copyTo(Img_in);
        Mat Img_out(Img_in.size(), CV_32FC3);
        Img_in.convertTo(Img_out, CV_32FC3);
        int n_row=Img_in.rows;
        int n_col=Img_in.cols;
        int P_size=5;
        int Q_size=5;
        float k1, k2;
        float m, n;
        int h,w;
//mosaic
        for (int i=P_size; i<n_row-P_size-1; i=i+P_size)
        {
            for (int j=Q_size; j<n_col-1-Q_size; j=j+Q_size)
            {
                k1=(double)((rand() % 100))/100.0-0.5;
                k2=(double)((rand() % 100))/100.0-0.5;

                m=(k1*(P_size*2-1));
                n=(k2*(Q_size*2-1));

                h=(int)(i+m)% n_row;
                w=(int)(j+n)% n_col;

                sub_mat=Img_out.operator()(Range(i-P_size,i+P_size), Range(j-Q_size,j+Q_size));
                sub_mat.setTo(Scalar(Img_in.at<Vec3b>(h,w)));
            }
        }
// 拿到原始图指定区域子图像的引用
        Mat dstRoi = tempImage(Rect(x, y,rect.width,rect.height));
// ROI子图像之间的复制
        Img_out.convertTo(dstRoi, dstRoi.type(), 1, 0);
        tempImage.copyTo(pictureView->currentCvMat);
        pictureView->imgCurrentHeight=pictureView->imgOriginalHeight;
        pictureView->imgCurrentWidth=pictureView->imgOriginalWidth;
        pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
        pictureView->updateCurrentImage();
    }
    else
    {
        return;
    }
}

void PictureMosaic::doEraser(QSizeF mosaicPoint, PictureView* pictureView,
                             int mosaicWidthHeight, bool rectFlag)
{
    if(rectFlag)
    {
        Mat Img_in;
//判断上一步是否有Filter
    if(filterFlag == true)
        {
            noMosaicFilter.copyTo(tmpImg);
            mosaicFlag = false;
        }
//判断上一步是否有MosaicBrush
    else if(mosaicFlag == true)
    {
        beforeMosaicImage.copyTo(tmpImg);
    }
        pictureView->currentCvMat.copyTo(this->tempImage);
        double x = mosaicPoint.width();
        double y = mosaicPoint.height();
        Rect rect(x, y, mosaicWidthHeight, mosaicWidthHeight);
//设置感兴趣区域,拷贝
        tmpImg(rect).copyTo(Img_in);
        Mat Img_out(Img_in.size(), CV_32FC3);
        Img_in.convertTo(Img_out, CV_32FC3);
// 拿到原始图指定区域子图像的引用
        Mat dstRoi = tempImage(Rect(x, y,rect.width,rect.height));
// ROI子图像之间的复制
        Img_out.convertTo(dstRoi, dstRoi.type(), 1, 0);
        tempImage.copyTo(pictureView->currentCvMat);
        pictureView->imgCurrentHeight=pictureView->imgOriginalHeight;
        pictureView->imgCurrentWidth=pictureView->imgOriginalWidth;
        pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
        pictureView->updateCurrentImage();
    }
    else
    {
        return;
    }
}

