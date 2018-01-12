#ifndef PICTUREFILTER
#define PICTUREFILTER
#include"all.h"
class PictureView;
class PictureFilter : public QWidget
{
    Q_OBJECT
public:
    PictureFilter();
    ~PictureFilter();

    void getBright(int pos_BrightSlider, PictureView* pictureView);
    void getContrast(int pos_ContrastSlider, PictureView* pictureView);
    void getColorSaturation(int pos_ColorSaturationSlider, PictureView* pictureView);
    void getResolution(int pos_ResolutionSlider, PictureView* pictureView);

//    cv::Mat& filterImage(int para, cv::Mat& mat, int filterKind);
//    cv::Mat& filterBrightSlider(int para, cv::Mat& mat);
//    cv::Mat& filterContrastSlider(int para, cv::Mat& mat);
//    cv::Mat& filterColorSaturationSlider(int para, cv::Mat& mat);
//    cv::Mat& filterResolutionSlider(int para, cv::Mat& mat);

    cv::Mat filterImage(int para, cv::Mat mat, int filterKind);
    cv::Mat noMosaicFilterImage(int para, cv::Mat mat, int filterKind);
    cv::Mat filterBrightSlider(int para, cv::Mat mat);
    cv::Mat filterContrastSlider(int para, cv::Mat mat);
    cv::Mat filterColorSaturationSlider(int para, cv::Mat mat);
    cv::Mat filterResolutionSlider(int para, cv::Mat mat);
    cv::Mat noMosaicFilterBrightSlider(int para, cv::Mat mat);
    cv::Mat noMosaicFilterContrastSlider(int para, cv::Mat mat);
    cv::Mat noMosaicFilterColorSaturationSlider(int para, cv::Mat mat);
    cv::Mat noMosaicFilterResolutionSlider(int para, cv::Mat mat);

    int clamp(int value, int min, int max);

private:
    cv::Mat pic;
    cv::Mat tempImage;
    cv::Mat tmpImg;
    cv::Mat dstBright;
    cv::Mat dstContrast;
    cv::Mat dstColorSaturation;
    cv::Mat dstResolution;
    cv::Mat dstBrightNoMosaic;
    cv::Mat dstContrastNoMosaic;
    cv::Mat dstColorSaturationNoMosaic;
    cv::Mat dstResolutionNoMosaic;

signals:
    void sig_upDateFilter(int para, PictureView* pictureView, int filterKind);
    void sig_upDateNoMosaicFilter(int para, PictureView* pictureView, int filterKind);
public slots:
    void slot_upDateFilter(int para, PictureView* pictureView, int filterKind);
    void slot_upDateNoMosaicFilter(int para, PictureView* pictureView, int filterKind);
};

#endif // PICTUREFILTER
