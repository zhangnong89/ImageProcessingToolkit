#include"picturefilter.h"
using namespace cv;
PictureFilter::PictureFilter()
    :QWidget()
{
    connect(this, SIGNAL(sig_upDateFilter(int, PictureView*, int)),
            this, SLOT(slot_upDateFilter(int, PictureView*, int)));
    connect(this, SIGNAL(sig_upDateNoMosaicFilter(int, PictureView*, int)),
            this, SLOT(slot_upDateNoMosaicFilter(int, PictureView*, int)));
}

PictureFilter::~PictureFilter()
{

}

//调节条的个数（调节的种类）
const int bar_num = 3;
const int noMosaicBar_num = 3;
//判断上次是否有此动作
bool flag[bar_num] = {false};
bool noMosaicFlag[noMosaicBar_num] = {false};
//传递给PictureMosaic
bool filterFlag = false;
Mat noMosaicFilter;

//接收函数
void PictureFilter::getBright(int pos_BrightSlider, PictureView* pictureView)
{
    int filterKind = 1;
    emit sig_upDateFilter(pos_BrightSlider, pictureView, filterKind);
    emit sig_upDateNoMosaicFilter(pos_BrightSlider, pictureView, filterKind);
}
//接收函数
void PictureFilter::getContrast(int pos_ContrastSlider, PictureView* pictureView)
{
    int filterKind = 2;
    emit sig_upDateFilter(pos_ContrastSlider, pictureView, filterKind);
    emit sig_upDateNoMosaicFilter(pos_ContrastSlider, pictureView, filterKind);
}
//接收函数
void PictureFilter::getColorSaturation(int pos_colorSaturationSlider, PictureView* pictureView)
{
    int filterKind = 3;
    emit sig_upDateFilter(pos_colorSaturationSlider, pictureView, filterKind);
    emit sig_upDateNoMosaicFilter(pos_colorSaturationSlider, pictureView, filterKind);
}
//接收函数
void PictureFilter::getResolution(int pos_resolutionSlider, PictureView* pictureView)
{
    int filterKind = 4;
    emit sig_upDateFilter(pos_resolutionSlider, pictureView, filterKind);
    emit sig_upDateNoMosaicFilter(pos_resolutionSlider, pictureView, filterKind);
}

void PictureFilter::slot_upDateFilter(int para, PictureView* pictureView, int filterKind)
{
    Mat mat;
    Mat src = pictureView->currentCvMat;
    mat = filterImage(para, src, filterKind);
//写入currentCvMat, 同时update
    mat.copyTo(pictureView->currentCvMat);
    pictureView->imgCurrentHeight=pictureView->imgOriginalHeight;
    pictureView->imgCurrentWidth=pictureView->imgOriginalWidth;
//    pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
    pictureView->updateCurrentImage();
}

//Mat& PictureFilter::filterImage(int para, Mat& src, int filterKind)
Mat PictureFilter::filterImage(int para, Mat src, int filterKind)
{
    if(filterKind==1)
    {
        pic = filterBrightSlider(para, src);
    }
    if(filterKind==2)
    {
        pic = filterContrastSlider(para, src);
    }
    if(filterKind==3)
    {
        pic = filterColorSaturationSlider(para, src);
    }
    if(filterKind==4)
    {
        pic = filterResolutionSlider(para, src);
    }
    return pic;
}

//Mat& PictureFilter::filterBrightSlider(int para, Mat& src)
Mat PictureFilter::filterBrightSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//判断之前是否进行此调节，如果否，则存储一张临时图片
     if(flag[0] == false)
    {
        src.copyTo(tempImage);
        for(int i=0; i< bar_num; i++)
        {
            flag[i] = false;
        }
    }
//再将临时图片复制
    tempImage.copyTo(src);
    flag[0] = true;
    dstBright = src;
        for (int i = 0;i<width;++i)
        for(int j= 0;j<height;++j)
            for(int k = 0;k<3;++k)
            {
                src.at<Vec3b>(i,j)[k] = clamp(src.at<Vec3b>(i,j)[k] + para, 0, 255);
                dstBright.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(src.at<Vec3b>(i,j)[k]);
            }
        return dstBright;
}

//Mat& PictureFilter::filterContrastSlider(int para, Mat& src)
Mat PictureFilter::filterContrastSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//判断之前是否进行此调节，如果否，则存储一张临时图片
    if(flag[1] == false)
    {
        src.copyTo(tempImage);
        for(int i=0; i< bar_num; i++)
        {
            flag[i] = false;
        }
    }
//再将临时图片复制
    tempImage.copyTo(src);
    flag[1] = true;
    dstContrast = src;

    float alpha;
    if(para == 0)
    {
        alpha=1;
    }
    else
    {
//调节范围
        alpha = (255 + para) / 255.0;
    }
    for (int i = 0;i<width;++i)
    for(int j= 0;j<height;++j)
        for(int k = 0;k<3;++k)
        {
            src.at<Vec3b>(i,j)[k] = clamp(alpha * (src.at<Vec3b>(i,j)[k] - 255/2) + 255/2, 0, 255);
            dstContrast.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(src.at<Vec3b>(i,j)[k]);
        }
    return dstContrast;
}

//Mat& PictureFilter::filterColorSaturationSlider(int para, Mat& src)
Mat PictureFilter::filterColorSaturationSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//判断之前是否进行此调节，如果否，则存储一张临时图片
    if(flag[2] == false)
    {
        src.copyTo(tempImage);
        for(int i=0; i< bar_num; i++)
            {
                flag[i] = false;
            }
        }
//再将临时图片复制
        tempImage.copyTo(src);
        flag[2] = true;
        dstColorSaturation = src;
//饱和度算法，先将RGB空间转化为HSV空间，再进行饱和度调节
        cvtColor(dstColorSaturation, dstColorSaturation, CV_BGR2HSV);
        for (int i = 0;i<width;++i)
        for(int j= 0;j<height;++j)
            for(int k = 0;k<3;++k)
            {
                dstColorSaturation.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(src.at<Vec3b>(i,j)[k] + para/10.0);
            }
        cvtColor(dstColorSaturation, dstColorSaturation, CV_HSV2BGR);
        return dstColorSaturation;
}

//Mat& PictureFilter::filterResolutionSlider(int para, Mat& src)
Mat PictureFilter::filterResolutionSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//阈值
    int threshold = 80;
    Vec3b bgr_0;
    Vec3b bgr_1;
    Vec3b bgr_2;
    uchar r_0, g_0, b_0;
    uchar r_1, g_1, b_1;
    uchar r_2, g_2, b_2;
    uchar gradientR, gradientG, gradientB;
//判断之前是否进行此调节，如果否，则存储一张临时图片
    if(flag[3] == false)
    {
        src.copyTo(tempImage);
        for(int i=0; i< bar_num; i++)
        {
            flag[i] = false;
        }
    }
//再将临时图片复制
    tempImage.copyTo(src);
    flag[3] = true;
    dstResolution = src;
//锐化算法,微分法中的梯度锐化
    for (int i = 0;i<width;++i)
    {
        for(int j= 0;j<height;++j)
        {
            bgr_0 = src.at<Vec3b>(i, j);
            bgr_1 = src.at<Vec3b>(i, (j+1));
            bgr_2 = src.at<Vec3b>((i+1), j);

            b_0 = saturate_cast<uchar>(bgr_0[0]);
            g_0 = saturate_cast<uchar>(bgr_0[1]);
            r_0 = saturate_cast<uchar>(bgr_0[2]);

            b_1 = saturate_cast<uchar>(bgr_1[0]);
            g_1 = saturate_cast<uchar>(bgr_1[1]);
            r_1 = saturate_cast<uchar>(bgr_1[2]);

            b_2 = saturate_cast<uchar>(bgr_2[0]);
            g_2 = saturate_cast<uchar>(bgr_2[1]);
            r_2 = saturate_cast<uchar>(bgr_2[2]);
//使用差分近似微分
            gradientB = abs(b_0 - b_1) + abs(b_0 - b_2);
            gradientG = abs(g_0 - g_1) + abs(g_0 - g_2);
            gradientR = abs(r_0 - r_1) + abs(r_0 - r_2);

            if(gradientB > threshold)
            {
                b_0 = qMin( gradientB + para, 255);
            }
            if(gradientG > threshold)
            {
                g_0 = qMin( gradientG + para, 255);
            }
            if(gradientR > threshold)
            {
                r_0 = qMin(gradientR + para, 255);
            }
            bgr_0[0] = b_0;
            bgr_0[1] = g_0;
            bgr_0[2] = r_0;
            dstResolution.at<Vec3b>(i, j) = bgr_0;
        }
    }
    return dstResolution;
}

/*****************************************************/
//为Mosaic传递参数
void PictureFilter::slot_upDateNoMosaicFilter(int para, PictureView* pictureView, int filterKind)
{
    //传递给PictureMosaic
    Mat noMosaic_src = pictureView->firstCvMat;
    noMosaicFilter = noMosaicFilterImage(para, noMosaic_src, filterKind);
    filterFlag = true;
}

Mat PictureFilter::noMosaicFilterImage(int para, Mat src, int filterKind)
{
    Mat noMosaicPic;
    if(filterKind==1)
    {
        noMosaicPic = noMosaicFilterBrightSlider(para, src);
    }
    if(filterKind==2)
    {
        noMosaicPic = noMosaicFilterContrastSlider(para, src);
    }
    if(filterKind==3)
    {
        noMosaicPic = noMosaicFilterColorSaturationSlider(para, src);
    }
    if(filterKind==4)
    {
        noMosaicPic = noMosaicFilterResolutionSlider(para, src);
    }
    return noMosaicPic;
}

//Mat& PictureFilter::filterBrightSlider(int para, Mat& src)
Mat PictureFilter::noMosaicFilterBrightSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//判断之前是否进行此调节，如果否，则存储一张临时图片
     if(noMosaicFlag[0] == false)
    {
        src.copyTo(tmpImg);
        for(int i=0; i< noMosaicBar_num; i++)
        {
            noMosaicFlag[i] = false;
        }
    }
//再将临时图片复制
    tmpImg.copyTo(src);
    noMosaicFlag[0] = true;
    dstBrightNoMosaic = src;
        for (int i = 0;i<width;++i)
        for(int j= 0;j<height;++j)
            for(int k = 0;k<3;++k)
            {
                src.at<Vec3b>(i,j)[k] = clamp(src.at<Vec3b>(i,j)[k] + para, 0, 255);
                dstBrightNoMosaic.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(src.at<Vec3b>(i,j)[k]);
            }
        return dstBrightNoMosaic;
}

//Mat& PictureFilter::filterContrastSlider(int para, Mat& src)
Mat PictureFilter::noMosaicFilterContrastSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//判断之前是否进行此调节，如果否，则存储一张临时图片
    if(noMosaicFlag[1] == false)
    {
        src.copyTo(tmpImg);
        for(int i=0; i< noMosaicBar_num; i++)
        {
            noMosaicFlag[i] = false;
        }
    }
//再将临时图片复制
    tmpImg.copyTo(src);
    noMosaicFlag[1] = true;
    dstContrastNoMosaic = src;

    float alpha;
    if(para == 0)
    {
        alpha=1;
    }
    else
    {
//调节范围
        alpha = (255 + para) / 255.0;
    }
    for (int i = 0;i<width;++i)
    for(int j= 0;j<height;++j)
        for(int k = 0;k<3;++k)
        {
            src.at<Vec3b>(i,j)[k] = clamp(alpha * (src.at<Vec3b>(i,j)[k] - 255/2) + 255/2, 0, 255);
            dstContrastNoMosaic.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(src.at<Vec3b>(i,j)[k]);
        }
    return dstContrastNoMosaic;
}

//Mat& PictureFilter::filterColorSaturationSlider(int para, Mat& src)
Mat PictureFilter::noMosaicFilterColorSaturationSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//判断之前是否进行此调节，如果否，则存储一张临时图片
    if(noMosaicFlag[2] == false)
    {
        src.copyTo(tmpImg);
        for(int i=0; i< noMosaicBar_num; i++)
            {
                noMosaicFlag[i] = false;
            }
        }
//再将临时图片复制
        tmpImg.copyTo(src);
        noMosaicFlag[2] = true;
        dstColorSaturationNoMosaic = src;
//饱和度算法，先将RGB空间转化为HSV空间，再进行饱和度调节
        cvtColor(dstColorSaturationNoMosaic, dstColorSaturationNoMosaic, CV_BGR2HSV);
        for (int i = 0;i<width;++i)
        for(int j= 0;j<height;++j)
            for(int k = 0;k<3;++k)
            {
                dstColorSaturationNoMosaic.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(src.at<Vec3b>(i,j)[k] + para/10.0);
            }
        cvtColor(dstColorSaturationNoMosaic, dstColorSaturationNoMosaic, CV_HSV2BGR);
        return dstColorSaturationNoMosaic;
}

//Mat& PictureFilter::filterResolutionSlider(int para, Mat& src)
Mat PictureFilter::noMosaicFilterResolutionSlider(int para, Mat src)
{
    int width = src.rows;
    int height = src.cols;
//阈值
    int threshold = 80;
    Vec3b bgr_0;
    Vec3b bgr_1;
    Vec3b bgr_2;
    uchar r_0, g_0, b_0;
    uchar r_1, g_1, b_1;
    uchar r_2, g_2, b_2;
    uchar gradientR, gradientG, gradientB;
//判断之前是否进行此调节，如果否，则存储一张临时图片
    if(noMosaicFlag[3] == false)
    {
        src.copyTo(tmpImg);
        for(int i=0; i< noMosaicBar_num; i++)
        {
            noMosaicFlag[i] = false;
        }
    }
//再将临时图片复制
    tmpImg.copyTo(src);
    noMosaicFlag[3] = true;
    dstResolutionNoMosaic = src;
//锐化算法,微分法中的梯度锐化
    for (int i = 0;i<width;++i)
    {
        for(int j= 0;j<height;++j)
        {
            bgr_0 = src.at<Vec3b>(i, j);
            bgr_1 = src.at<Vec3b>(i, (j+1));
            bgr_2 = src.at<Vec3b>((i+1), j);

            b_0 = saturate_cast<uchar>(bgr_0[0]);
            g_0 = saturate_cast<uchar>(bgr_0[1]);
            r_0 = saturate_cast<uchar>(bgr_0[2]);

            b_1 = saturate_cast<uchar>(bgr_1[0]);
            g_1 = saturate_cast<uchar>(bgr_1[1]);
            r_1 = saturate_cast<uchar>(bgr_1[2]);

            b_2 = saturate_cast<uchar>(bgr_2[0]);
            g_2 = saturate_cast<uchar>(bgr_2[1]);
            r_2 = saturate_cast<uchar>(bgr_2[2]);
//使用差分近似微分
            gradientB = abs(b_0 - b_1) + abs(b_0 - b_2);
            gradientG = abs(g_0 - g_1) + abs(g_0 - g_2);
            gradientR = abs(r_0 - r_1) + abs(r_0 - r_2);

            if(gradientB > threshold)
            {
                b_0 = qMin( gradientB + para, 255);
            }
            if(gradientG > threshold)
            {
                g_0 = qMin( gradientG + para, 255);
            }
            if(gradientR > threshold)
            {
                r_0 = qMin(gradientR + para, 255);
            }
            bgr_0[0] = b_0;
            bgr_0[1] = g_0;
            bgr_0[2] = r_0;
            dstResolutionNoMosaic.at<Vec3b>(i, j) = bgr_0;
        }
    }
    return dstResolutionNoMosaic;
}

int PictureFilter::clamp(int value, int min, int max)
{
    if(value>max) return max;
    if(value<min) return min;
    return value;
}

