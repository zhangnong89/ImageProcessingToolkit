#include"pictureproperties.h"

pictureProperties::pictureProperties(QWidget *parent):QDialog(parent)
{
        this->setFixedSize(435,280);
        this->setAutoFillBackground(true);        

//        this->setFrameShape(QFrame::NoFrame);
//        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->setWindowTitle("图片属性");
//        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

/********************************Label****************************************/
        picNameLabel=new QLabel("图片名称:",this);
        picPathLabel=new QLabel("图片路径:",this);
        picTypeLabel=new QLabel("图片类型:",this);
        picSizeLabel=new QLabel("图片尺寸:",this);
        fileSizeLabel=new QLabel("文件大小:",this);
        picShootingLabel=new QLabel("拍摄时间:",this);
        cameraManufacturerLabel=new QLabel("相机厂商:",this);
        cameraModelLabel=new QLabel("设备型号:",this);
        cameralLensLabel=new QLabel("相机镜头:",this);
        shutterCountLabel=new QLabel("快门次数:",this);

//        shutterCountLabel->setFixedWidth(55);
//second coloum
        shutterSpeedLabel=new QLabel("快门速度:",this);
        apertureValueLabel=new QLabel("光圈值:",this);
        focusLabel=new QLabel("焦距:",this);
        sensitivityLabel=new QLabel("感光度:",this);
        exposureCompensationLabel=new QLabel("曝光补偿:",this);
        flashLampLabel=new QLabel("闪光灯:",this);
        whiteBalanceLabel=new QLabel("白平衡:",this);
        shootingModeLabel=new QLabel("拍摄模式:",this);
        meteringLabel=new QLabel("测光模式:",this);
/******************************/
        picNameLabel->setGeometry(15,5,50,25);//225
        picPathLabel->setGeometry(15,25,50,25);
        picTypeLabel->setGeometry(15,45,50,25);
        picSizeLabel->setGeometry(15,65,50,25);
        fileSizeLabel->setGeometry(15,85,50,25);
        picShootingLabel->setGeometry(15,105,50,25);

        cameraManufacturerLabel->setGeometry(15,125,50,25);
        cameraModelLabel->setGeometry(15,145,50,25);
        cameralLensLabel->setGeometry(15,165,50,25);
        shutterCountLabel->setGeometry(15,185,50,25);
//second coloum
        shutterSpeedLabel->setGeometry(230,5,50,25);
        apertureValueLabel->setGeometry(230,25,50,25);
        focusLabel->setGeometry(230,45,50,25);
        sensitivityLabel->setGeometry(230,65,50,25);
        exposureCompensationLabel->setGeometry(230,85,50,25);
        flashLampLabel->setGeometry(230,105,50,25);
        whiteBalanceLabel->setGeometry(230,125,50,25);
        shootingModeLabel->setGeometry(230,145,50,25);
        meteringLabel->setGeometry(230,165,50,25);

/********************************Data****************************************/
        picNameData=new QLabel(this);
        picPathData=new QLabel(this);
        picTypeData=new QLabel(this);
        picSizeData=new QLabel(this);
        fileSizeData=new QLabel(this);
        picShootingData=new QLabel(this);
        cameraManufacturerData=new QLabel(this);
        cameraModelData=new QLabel(this);
        cameralLensData=new QLabel(this);
        shutterCountData=new QLabel(this);
//second coloum
        shutterSpeedData=new QLabel(this);
        apertureValueData=new QLabel(this);
        focusData=new QLabel(this);
        sensitivityData=new QLabel(this);
        exposureCompensationData=new QLabel(this);
        flashLampData=new QLabel(this);
        whiteBalanceData=new QLabel(this);
        shootingModeData=new QLabel(this);
        meteringData=new QLabel(this);
/******************************/
        picNameData->setGeometry(68,5,150,25);
        picPathData->setGeometry(68,25,150,25);
        picTypeData->setGeometry(68,45,150,25);
        picSizeData->setGeometry(68,65,150,25);
        fileSizeData->setGeometry(68,85,150,25);
        picShootingData->setGeometry(68,105,150,25);
        cameraManufacturerData->setGeometry(68,125,150,25);
        cameraModelData->setGeometry(68,145,150,25);
        cameralLensData->setGeometry(68,165,150,25);
        shutterCountData->setGeometry(68,185,150,25);
//cesond coloum
        shutterSpeedData->setGeometry(282,5,150,25);
        apertureValueData->setGeometry(282,25,150,25);
        focusData->setGeometry(282,45,150,25);
        sensitivityData->setGeometry(282,65,150,25);
        exposureCompensationData->setGeometry(282,85,150,25);
        flashLampData->setGeometry(282,105,150,25);
        whiteBalanceData->setGeometry(282,125,150,25);
        shootingModeData->setGeometry(282,145,150,25);
        meteringData->setGeometry(282,165,150,25);


        QVBoxLayout *vbox = new QVBoxLayout;
        QWidget *widget = new QWidget;
        widget->setLayout(vbox);
//        setStyleSheet("background: rgb(127, 127, 127,100);");
//        widget->setStyleSheet("color: grey");
}
pictureProperties::~pictureProperties(){}

void pictureProperties::elideTextSeting(QLabel *label,QString fullText)
{
        QFontMetrics fm=label->fontMetrics();
        QString showText=fm.elidedText(fullText,Qt::ElideRight,label->width());
        label->setText(showText);
        if(showText != fullText)
        {
            label->setToolTip(fullText.left(1024));
        }
        else
        {
            label->setToolTip("");
        }

}

void pictureProperties::updateData(CellItem*cellItem)
{
//        QFontMetrics fm=picNameData->fontMetrics();
//         showText=fm.elidedText(cellItem->getImageName(),Qt::ElideRight,picNameData->width());
//        picNameData->setText(showText);

        elideTextSeting(picNameData,cellItem->getImageName());
        elideTextSeting(picPathData,cellItem->getImagePath());

        picTypeData->setText(cellItem->getImageType());
        picSizeData->setText(cellItem->getImageSize());
        fileSizeData->setText(cellItem->getImageFileSize());
        picShootingData->setText(cellItem->getImageShootTime());
        cameraManufacturerData->setText(cellItem->getImageCameraManufacturer());
        elideTextSeting(cameraModelData,cellItem->getImageCameraModel());
//        cameraModelData->setText(cellItem->getImageCameraModel());
        cameralLensData->setText(cellItem->getImageCameraLens());
        shutterCountData->setText(cellItem->getImageShutterCount());
//second coloum
        shutterSpeedData->setText(cellItem->getImageShutterSpeed());
        apertureValueData->setText(cellItem->getImageApertureValue());
        focusData->setText(cellItem->getImageFocus());
        sensitivityData->setText(cellItem->getImageSensitivity());
        exposureCompensationData->setText(cellItem->getImageExposureCompensation());
        flashLampData->setText(cellItem->getImageFlashLamp());
        whiteBalanceData->setText(cellItem->getImageWhiteBalance());
        shootingModeData->setText(cellItem->getImageShootingModel());
        meteringData->setText(cellItem->getImageMeteringLabel());
}
