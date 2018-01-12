#ifndef MAINPAGE_H
#define MAINPAGE_H
//#include "pictureview.h"
#include"all.h"

class PictureView;
class TopMenuBar;
class SideMenuBar;
class PictureShotDialog;
class AdjustSizeDialog;
class UnderTopMenuBar;
class AdvanceSetting;
class PictureMosaic;
class PictureFormatConvert;
class PictureFilter;
class QThread;
class ComparePage;
class PicturePuzzle;
class PictureStackedWidget;
//struct stackList *StackList;

class MainPage : public QWidget
{
    Q_OBJECT
public:
     explicit MainPage(QWidget *parent = 0);
     QString currentFilePath;                          //当前显示的图片的绝对路径
     QString originalFilePath;
     PictureView *pictureView; //create the view to show current picture;
    ~MainPage();
     TopMenuBar *topMenuBar;
     SideMenuBar *sideMenuBar;
//     UnderTopMenuBar *underTopMenuBar ;

    QImage  temQimg;
//    IplImage* iplImg;//用来加载图片的图片结构指针
//    IplImage *tempIplImg;//临时存储图片结构的指针
    QImage *qImg;//QT的QImage图像指针
    cv::Mat tempImage;
    int width;
    int height;

    PictureShotDialog *pdialog;
    PictureMosaic* pictureMosaic;
    PictureFormatConvert* pictureFormatConvert;
    ComparePage* comparePage;
    PicturePuzzle* picturePuzzle;
//    QStackedWidget *stackedWidget;
    PictureStackedWidget* pictureStackedWidget;

    bool cutFlag;
    bool releaseFilterFlag;
    bool releaseMosaicFlag;
    bool releaseMosaicEraserFlag;
    bool isDoMosaicFlag;
    bool btnCompareIsPressed;
    AdjustSizeDialog*freeCutDialog;
    PictureFilter * pictureFilter;

/*create a stack*/
    struct stackList*fileStackList;
    int startPush(struct stackList*ps,QString &pItem,int flag);
    QString lastOperation;
/*create a redo stack*/
    struct stackList*redoStackList;

//picture rotate function
    void rotateImage(double angle,double scale);
    QString savePixFile(QPixmap &pix);

protected:
    void modelCutApi(int x, int y, int width, int height);
    void modelChangeSize(int width,int height);


signals:
    void sig_openFile(QString fileName);        //点击“打开文件”发送此信号
    void sig_receiveCurrentImage(const QString&);   //send the current image to compare
    void sig_receiveFirstImage(const QString &);    //send the original image to compare
    void sig_receiveFirstImg(const QString&); //send the current image to puzzle

public slots:
     void slot_receivePictureFileName(const QString &);
     void slot_rotateLeftCvPicture();
     void slot_rotateRightCvPicture();
     void slot_rotateFrontCvPicture();
     void slot_rotateBackCvPicture();

     void slot_narrowCurrentImage();
     void slot_enlargeCurrentImage();
//cut callbackup function
     void slot_freeCutting();
     void slot_pictureCut();
     void slot_finishedCutting();
     void slot_normalWallCut();
     void slot_wideWallCut();
     void slot_inch1Cut();
     void slot_inch2Cut();
     void slot_freeAdjustSize();
     void slot_w800();
     void slot_w1200();
     void slot_w1600();
     void freeAdjustSizeCallback();
     //filter slots
     void slot_BrightSlider(int);
     void slot_ContrastSlider(int);
     void slot_colorSaturationSlider(int);
     void slot_resolutionSlider(int);
     void slot_sliderIsReleased();
     //mosaic slots
     void slot_mosaicBrush();
     void slot_mosaicEraser();
     void slot_doMosaic(QMouseEvent*);
     void slot_doEraser(QMouseEvent*);
     void slot_mouseIsReleased();
     void slot_mouseEraserIsReleased();
     //formatConvert
    void slot_formatConvert();
     //puzzle
    void slot_templatePuzzlePress();
    void slot_puzzle_1();
    void slot_puzzle_2();
    void slot_puzzle_3();
    void slot_puzzle_4();
    void slot_freePuzzlePress();
/*top menu bar callback function*/
    void slot_undo();
    void slot_redo();
    void slot_reset();
    void slot_save();
    void slot_saveAs();
//compare
    void slot_btnCompareIsPressed();


};

#endif // MAINPAGE_H
