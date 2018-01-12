#ifndef PICTUREPROPERTIES
#define PICTUREPROPERTIES
#include"all.h"
class CellItem;

class pictureProperties:public QDialog
{
    Q_OBJECT
public:
    pictureProperties(QWidget *parent = 0);
    ~pictureProperties();
//update the label data
    void updateData(CellItem*cellItem);
    void elideTextSeting(QLabel*label,QString fullText);
private:
/******************************widget*************************/
//first coloum
    QLabel*picNameLabel;
    QLabel*picPathLabel;
    QLabel*picTypeLabel;
    QLabel*picSizeLabel;
    QLabel*fileSizeLabel;
    QLabel*picShootingLabel;
    QLabel*cameraManufacturerLabel;
    QLabel*cameraModelLabel;
    QLabel*cameralLensLabel;
    QLabel*shutterCountLabel;
//second coloum
    QLabel*shutterSpeedLabel;
    QLabel*apertureValueLabel;
    QLabel*focusLabel;
    QLabel*sensitivityLabel;
    QLabel*exposureCompensationLabel;
    QLabel*flashLampLabel;
    QLabel*whiteBalanceLabel;
    QLabel*shootingModeLabel;
    QLabel*meteringLabel;

/**************************data**************************/
//first coloum
        QLabel*picNameData;
        QLabel*picPathData;
        QLabel*picTypeData;
        QLabel*picSizeData;
        QLabel*fileSizeData;
        QLabel*picShootingData;
        QLabel*cameraManufacturerData;
        QLabel*cameraModelData;
        QLabel*cameralLensData;
        QLabel*shutterCountData;
    //second coloum
        QLabel*shutterSpeedData;
        QLabel*apertureValueData;
        QLabel*focusData;
        QLabel*sensitivityData;
        QLabel*exposureCompensationData;
        QLabel*flashLampData;
        QLabel*whiteBalanceData;
        QLabel*shootingModeData;
        QLabel*meteringData;



public slots:

};
#endif // PICTUREPROPERTIES

