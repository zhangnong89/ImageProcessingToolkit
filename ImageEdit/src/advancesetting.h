#ifndef ADVANCESETTING
#define ADVANCESETTING
#include"all.h"
//高级设置页
class QPainter;
class AdvanceSetting: public QScrollArea
{
    Q_OBJECT

public:
    explicit AdvanceSetting(QWidget *parent = 0);
//    void paintEvent(QPaintEvent *e);
//生成添加了数字的新图像
    void imageNumber(QLabel *label);
    QSlider *BrightSlider;
    QSlider *ContrastSlider;
    QSlider *colorSaturationSlider;
    QSlider *resolutionSlider;
    QLabel *brightPerLbl;
    QLabel *contrastPerLbl;
    QLabel *colorSaturationPerLbl;
    QLabel *resolutionPerLbl;
    QPushButton *mosaicBrush ;
    QPushButton *mosaicEraser;
    QLineEdit* convertEdit;
    QComboBox* convertCombo;
    QPushButton* convertBtn;
    QDateTime* dateTime;
    QString current_date;
    ~AdvanceSetting();
signals:
    void sig_BrightSlider(int);
    void sig_ContrastSlider(int);
    void sig_colorSaturationSlider(int);
    void sig_resolutionSlider(int);
    void sig_sliderIsReleased();
    void sig_mosaicBrush();
    void sig_mosaicEraser();
    void sig_formatConvert();
    void sig_convertBegin(QString&, QString&);
public slots:
    void slot_BrightSetValue(int);
    void slot_ContrastSetValue(int);
    void slot_colorSaturationSetValue(int);
    void slot_resolutionSetValue(int);
    void slot_initSlider();
    void slot_convertBegin();
    void slot_convertSuccess();
};

#endif // ADVANCESETTING

