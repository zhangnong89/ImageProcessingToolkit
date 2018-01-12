#include"cellitem.h"
#include <QWidget>
CellItem::CellItem(QString fileName,QWidget *parent ):QWidget(parent)
{
    EXIFINFO* info;
    Cexif*fileInfo=new Cexif(info);
//    qDebug()<<fileName.toStdString().c_str();
//    char *str=fileName.toStdString().c_str();
    fp=fopen(fileName.toStdString().c_str(),"r");
    if(NULL == fp)
    {
        qDebug()<<"failed to open file";
    }
    else
    {
        fileInfo->DecodeExif(fp);
        setImageInfo(info,fileName);
    }
}

/// Destructor of CellItem
CellItem::~CellItem()
{
    fclose(fp);
    fp=NULL;
}

QString CellItem::obtainFileType(QString &fileName)
{
        QImageReader imageReader;
        QByteArray format = imageReader.imageFormat(fileName);
        return format;
}
QString CellItem::obtainFileSize(QString &fileName)
{
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            return 0;
        }
        else
        {
            char unit='B';
            qreal curSize=file.size();
//            quint64 curSize=file.size();
            if(curSize > 1000)
            {
                    curSize/=1000;
                    unit='K';
                    if(curSize > 1000)
                    {
                            curSize/=1000;
                            unit='M';
                            if(curSize > 1000)
                            {
                                    curSize/=1000;
                                    unit='G';
                            }
                    }
            }
                return QString::number(curSize,'f',1)+QString("%1").arg(unit);
//            return QString("%1").arg(curSize)+QString("%1").arg(unit);
        }
}
QString CellItem::obtainExposureTime(float value)
{
        value=1/value;
        return "1/"+QString::number(value,'f',0)+"s";
}
QString CellItem::obtainFalshLamp(int value)
{
    QString tempStr=NULL;
    switch (value) {
    case 0:
        tempStr= "关";
        break;
    case 1:
        tempStr= "开";
        break;
    case 5:
        tempStr= "没有检测反射光";
        break;
    case 7:
        tempStr= "检测了反射光";
        break;
    default:
        tempStr="关";
        break;
    }
    return tempStr;
}
QString CellItem::obtainWhiteBalance(int value)
{
    QString tempStr=NULL;
    switch (value) {
    case 0:
        tempStr="自动";
        break;
    default:
        tempStr="手动";
        break;
    }
    return tempStr;
}

QString CellItem::obtainMeteringMode(int value)
{
    QString tempStr=NULL;
    switch (value) {
    case 0:
        tempStr="";
        break;
    case 1:
        tempStr="平均测光";
        break;
    case 2:
        tempStr= "中央重点测光";
        break;
    case 3:
        tempStr= "点测光";
        break;
    case 4:
        tempStr= "多点测光";
        break;
    case 5:
        tempStr="加权测光";
        break;
    case 6:
        tempStr="部分测光";
        break;
    default:
        tempStr="";
        break;
    }
    return tempStr;
}
QString CellItem::obtainShootingMode(unsigned long value)
{
    QString tempStr=NULL;
    switch (value) {
    case 0:
        tempStr= "标准模式";
        break;
    case 1:
        tempStr= "未知";
        break;
    case 2:
        tempStr="快速模式";
        break;
    case 3:
        tempStr="全景模式";
        break;
    default:
        tempStr="";
        break;
    }
    return tempStr;
}
QString CellItem::obtainFileName(QString &fileName)
{
        QString fileFull;
        QFileInfo fileInfo;
//        fileFull=QFileDialog::getOpenFileName(this);
        fileInfo=QFileInfo(fileName);
        return fileInfo.fileName();
}

QSize CellItem::obtainImageHeightAndWidth(const QString &filename)
{
    QImageReader imgReader(filename);
    return imgReader.size();
}

void CellItem::setImageInfo(EXIFINFO *info,QString &fileName)
    {

        imageName=obtainFileName(fileName);
        imagePath=fileName;
        imageType=obtainFileType(fileName);
//        imageSize=QString("%1").arg(info->Width)+" x "+QString("%1").arg(info->Height);
        imageSize=QString::number(obtainImageHeightAndWidth(fileName).width())+" x " + QString::number(obtainImageHeightAndWidth(fileName).height());
        imageFileSize=obtainFileSize(fileName);

         if(!info) return;
//check the current picture has EXIF infomation
        if((imageType == "jpeg") && (info->IsExif) &&(info->ApertureFNumber))
        {
            imageShootTime=info->DateTime;
            imageCameraManufacturer=info->CameraMake;
            imageCameraModel=info->CameraModel;
            imageCameraLens="";
            imageShutterCount="";
    //second coloum
            imageShutterSpeed=obtainExposureTime(info->ExposureTime);
            imageApertureValue="F"+QString("%1").arg(info->ApertureFNumber)+".0";
            imageFocus=QString("%1").arg(info->FocalLength)+"mm";
            imageSensitivity="ISO"+QString("%1").arg(info->ISOequivalent);
            imageExposureCompensation=QString::number(info->ExposureBias,'f',1);
            imageFlashLamp=obtainFalshLamp(info->FlashUsed);
            imageWhiteBalance=obtainWhiteBalance(info->Whitebalance);
            imageShootingModel=obtainShootingMode(info->SpecialMode);
            imageMetering=obtainMeteringMode(info->MeteringMode);
        }
}


























