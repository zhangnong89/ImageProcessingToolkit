#ifndef CELLITEM
#define CELLITEM
#include"all.h"
//struct EXIFINFO;

class CellItem : public QWidget
{
    Q_OBJECT

public:
     CellItem(QString fileName,QWidget *parent = 0);
    ~CellItem();
     FILE*fp;

     void setImageInfo( struct tag_ExifInfo* info,QString &fileName);
     QString obtainFileName(QString &fileName);
//     QString
     QString obtainFileType(QString &fileName);
     QString obtainFileSize(QString &fileName);
     QString obtainExposureTime(float value);
     QString obtainFalshLamp(int value);
     QString obtainWhiteBalance(int value);
     QString obtainMeteringMode(int value);
     QString obtainShootingMode(unsigned long value);
     QSize obtainImageHeightAndWidth(const QString &filename);

     QString getImageName()
     {
         return imageName;
     }
     QString getImagePath()
     {
         return imagePath;
     }
     QString getImageType()
     {
         return imageType;
     }
     QString getImageSize()
     {
         return imageSize;
     }
     QString getImageFileSize()
     {
         return imageFileSize;
     }
     QString getImageShootTime()
     {
         return imageShootTime;
     }
     QString getImageCameraManufacturer()
     {
         return imageCameraManufacturer;
     }
     QString getImageCameraModel()
     {
         return imageCameraModel;
     }
     QString getImageCameraLens()
     {
         return imageCameraLens;
     }
     QString getImageShutterCount()
     {
         return imageShutterCount;
     }
//second coloum
     QString getImageShutterSpeed()
     {
         return imageShutterSpeed;
     }
     QString getImageApertureValue()
     {
         return imageApertureValue;
     }
     QString getImageFocus()
     {
         return imageFocus;
     }
     QString getImageSensitivity()
     {
         return imageSensitivity;
     }
     QString getImageExposureCompensation()
     {
         return imageExposureCompensation;
     }
     QString getImageFlashLamp()
     {
         return imageFlashLamp;
     }
     QString getImageWhiteBalance()
     {
         return imageWhiteBalance;
     }
     QString getImageShootingModel()
     {
         return imageShootingModel;
     }
     QString getImageMeteringLabel()
     {
         return imageMetering;
     }



private:
     QString imageName;//
     QString imagePath;
     QString imageType;
     QString imageSize;
     QString imageFileSize;
     QString imageShootTime;//拍摄时间
     QString imageCameraManufacturer;//相机生产厂家
     QString imageCameraModel;//设备型号
     QString imageCameraLens;//
     QString imageShutterCount;
//second coloum
     QString imageShutterSpeed;//快门速度
     QString imageApertureValue;//光圈值
     QString imageFocus;//焦距
     QString imageSensitivity;//感光度
     QString imageExposureCompensation;//曝光补偿
     QString imageFlashLamp;//闪光灯
     QString imageWhiteBalance;//白平衡
     QString imageShootingModel;//拍摄模式
     QString imageMetering;//测光模式
signals:

public slots:
};



#endif // CELLITEM

