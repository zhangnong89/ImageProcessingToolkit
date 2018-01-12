#ifndef BOTTOMMENU
#define BOTTOMMENU
#include"all.h"
class pictureProperties;
class CellItem;
/*******************底部菜单栏************************/
class BottomMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit BottomMenuBar(QWidget *parent = 0);
    ~BottomMenuBar();
    pictureProperties*picProperties;
    CellItem*cellItem;
    QPushButton *picInfo;        //属性按钮
    QLabel *sizeLbl;               //尺寸label
    QPushButton *btnPrevious;//last picture
    QPushButton *btnNext;//next picture
    QPushButton *btnRemove;//remove the current picture

    QPushButton *btnFullScreen;//fullscreeb button
    QPushButton *btnFitScreen ;//fit screen button
    QPushButton *btnOriginalSize;//original size button

    QPushButton *picNarrow;
    QSlider *picSlider;
    QPushButton *picEnlarge;

    QHBoxLayout *picBottomRightHbox;

    void updateSizeLabel(QString fileName);
    void paintEvent(QPaintEvent *e);

//    void resizeEvent(QResizeEvent *e);  //设置属性按钮 和 尺寸label的位置
//    void mousePressEvent(QMouseEvent *event);//mouse press event
//    void mouseMoveEvent(QMouseEvent *event);
private:
    QString currentFileName;
    qreal picSliderValue;

signals:
    void sig_picAdjustSize(bool);

public slots:
    void picInfoCallbackFunc();
    void enablePicInfoCallbackFunc(QString fileName);
    void slot_picNarrow();
    void slot_picEnlarge();
    void slot_picSliderEvent(int);
};
#endif // BOTTOMMENU

