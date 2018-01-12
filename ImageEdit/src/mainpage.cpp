#include "mainpage.h"
#include "menu.h"
using namespace cv;
MainPage::MainPage(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));

    cutFlag=false;
    releaseFilterFlag = false;
    releaseMosaicFlag = false;
    isDoMosaicFlag = false;
    releaseMosaicEraserFlag = false;

    topMenuBar= new TopMenuBar;
//    underTopMenuBar = new UnderTopMenuBar;
    pictureView= new PictureView(currentFilePath);
    pictureFilter = new PictureFilter();
    pictureFormatConvert = new PictureFormatConvert();
    comparePage = new ComparePage;
    picturePuzzle = new PicturePuzzle;
    pictureStackedWidget = new PictureStackedWidget(pictureView);

    QVBoxLayout *mainVbox1 = new QVBoxLayout;
    mainVbox1->setSpacing(0);
    mainVbox1->setMargin(0);

    mainVbox1->addWidget(topMenuBar);
//    mainVbox1->addWidget(underTopMenuBar);

     sideMenuBar= new SideMenuBar;
    QHBoxLayout *mainVbox2 = new QHBoxLayout;
    mainVbox2->setSpacing(0);
    mainVbox2->setMargin(0);
    mainVbox2->addWidget(pictureStackedWidget);
    mainVbox2->addWidget(sideMenuBar);

    QVBoxLayout *t_main_hl = new QVBoxLayout;
    t_main_hl->setContentsMargins(0,0,0,0);
    t_main_hl->setSpacing(0);

    t_main_hl->addLayout(mainVbox1);
    t_main_hl->addLayout(mainVbox2);

    setLayout(t_main_hl);

/*initial the stack list*/
    fileStackList = new StackList;
    fileStackList->top=NULL;
    fileStackList->num=0;

    redoStackList = new StackList;
    redoStackList->top = NULL;
    redoStackList->num = 0;

    connect(topMenuBar,SIGNAL(sig_openFile(QString)),this,SLOT(slot_receivePictureFileName(QString)));
//新载入图片时，将Slider初始化
    connect(this->topMenuBar,SIGNAL(sig_initSlider()),this->sideMenuBar->advanceSettings,SLOT(slot_initSlider()));
//opencv
    connect(sideMenuBar->basicSettings,SIGNAL(sig_rotateLeft()),this,SLOT(slot_rotateLeftCvPicture()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_rotateRight()),this,SLOT(slot_rotateRightCvPicture()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_rotateFront()),this,SLOT(slot_rotateFrontCvPicture()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_rotateBack()),this,SLOT(slot_rotateBackCvPicture()));
//cutting event
    connect(sideMenuBar->basicSettings,SIGNAL(sig_freeCutting()),this,SLOT(slot_freeCutting()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_pictureCut()),this,SLOT(slot_pictureCut()));

    connect(sideMenuBar->basicSettings,SIGNAL(sig_normalWallCut()),this,SLOT(slot_normalWallCut()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_wideWallCut()),this,SLOT(slot_wideWallCut()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_inch1Cut()),this,SLOT(slot_inch1Cut()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_inch2Cut()),this,SLOT(slot_inch2Cut()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_freeAdjustSize()),this,SLOT(slot_freeAdjustSize()));

    connect(sideMenuBar->basicSettings,SIGNAL(sig_w800()),this,SLOT(slot_w800()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_w1200()),this,SLOT(slot_w1200()));
    connect(sideMenuBar->basicSettings,SIGNAL(sig_w1600()),this,SLOT(slot_w1600()));
//filter
     connect(sideMenuBar->advanceSettings,SIGNAL(sig_BrightSlider(int)),this,SLOT(slot_BrightSlider(int)));
     connect(sideMenuBar->advanceSettings,SIGNAL(sig_ContrastSlider(int)),this,SLOT(slot_ContrastSlider(int)));
     connect(sideMenuBar->advanceSettings,SIGNAL(sig_colorSaturationSlider(int)),this,SLOT(slot_colorSaturationSlider(int)));
     connect(sideMenuBar->advanceSettings,SIGNAL(sig_resolutionSlider(int)),this,SLOT(slot_resolutionSlider(int)));
//filter slider released
     connect(sideMenuBar->advanceSettings, SIGNAL(sig_sliderIsReleased()), this, SLOT(slot_sliderIsReleased()));
//Mosaic
     connect(sideMenuBar->advanceSettings,SIGNAL(sig_mosaicBrush()),this,SLOT(slot_mosaicBrush()));
     connect(sideMenuBar->advanceSettings,SIGNAL(sig_mosaicEraser()),this,SLOT(slot_mosaicEraser()));
//FormatConvert
     connect(sideMenuBar->advanceSettings, SIGNAL(sig_formatConvert()), this, SLOT(slot_formatConvert()));
     connect(sideMenuBar->advanceSettings, SIGNAL(sig_convertBegin(QString&,QString&)), pictureFormatConvert, SLOT(slot_convertGetText(QString&, QString&)));
     connect(pictureFormatConvert, SIGNAL(sig_convertFinish()), sideMenuBar->advanceSettings, SLOT(slot_convertSuccess()));
//puzzle
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_templatePuzzlePress()), this, SLOT(slot_templatePuzzlePress()));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_puzzle_1()), this, SLOT(slot_puzzle_1()));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_puzzle_2()), this, SLOT(slot_puzzle_2()));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_puzzle_3()), this, SLOT(slot_puzzle_3()));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_puzzle_4()), this, SLOT(slot_puzzle_4()));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_freePuzzlePress()), this, SLOT(slot_freePuzzlePress()));
    connect(this, SIGNAL(sig_receiveFirstImg(QString)), this->pictureStackedWidget->picturePuzzle, SLOT(slot_receiveFirstImg(QString)));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_puzzle_openNewFile()), this->pictureStackedWidget->picturePuzzle, SLOT(slot_openFileDialog()));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_puzzle_save()), this->pictureStackedWidget->picturePuzzle, SLOT(slot_puzzle_save()));
    connect(this->pictureStackedWidget->picturePuzzle, SIGNAL(sig_puzzle_saveSuccess()), sideMenuBar->puzzleSettings, SLOT(slot_puzzle_saveSuccess()));
    connect(sideMenuBar->puzzleSettings, SIGNAL(sig_templatePuzzlePress()), this->pictureStackedWidget, SLOT(slot_changePage2()));
    connect(sideMenuBar->t_primary, SIGNAL(clicked()), this->pictureStackedWidget, SLOT(slot_changePage0()));
    connect(sideMenuBar->t_senior, SIGNAL(clicked()), this->pictureStackedWidget, SLOT(slot_changePage0()));
//top menu bar function
    connect(topMenuBar->btnUndo,SIGNAL(clicked()),this,SLOT(slot_undo()));
    connect(topMenuBar->btnRedo,SIGNAL(clicked()),this,SLOT(slot_redo()));
    connect(topMenuBar->btnReset,SIGNAL(clicked()),this,SLOT(slot_reset()));
    connect(topMenuBar->btnSave,SIGNAL(clicked()),this,SLOT(slot_save()));
    connect(topMenuBar->btnSaveAs,SIGNAL(clicked()),this,SLOT(slot_saveAs()));

//Compare
    connect(topMenuBar->btnCompare, SIGNAL(pressed()), this, SLOT(slot_btnCompareIsPressed()));
    connect(topMenuBar->btnCompare, SIGNAL(pressed()), this->pictureStackedWidget, SLOT(slot_changePage1()));
    connect(topMenuBar->btnCompare, SIGNAL(released()), this->pictureStackedWidget, SLOT(slot_changePage0()));
    connect(this, SIGNAL(sig_receiveCurrentImage(QString)), this->pictureStackedWidget->comparePage, SLOT(slot_receiveCurrentImage(QString)));
    connect(this, SIGNAL(sig_receiveFirstImage(QString)), this->pictureStackedWidget->comparePage, SLOT(slot_receiveFirstImage(QString)));

}
/*picture editor save the current operation as the gaving name which the user can modify*/
void MainPage::slot_saveAs()
{
    QString fileName;
    QString currentFile = originalFilePath;
    int index = originalFilePath.lastIndexOf('.');
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");

    QString stackItem = NULL;
    stackListGetTop(fileStackList,stackItem);

    if(-1 == index)
    {
        currentFile += "_"+currentDate;
    }
    else
    {
        currentFile.insert(index,"_"+currentDate);
    }
    fileName = QFileDialog::getSaveFileName(this,tr("另存为"),currentFile);
    if(QFile::exists(fileName))
    {
        QFile::remove(fileName);
    }
    QFile::copy(stackItem,fileName);
}

/*picture editor save the current operation as the default name */
void MainPage::slot_save()
{
    qDebug()<<"slot_save";
    QString stackItem = NULL;

    stackListGetTop(fileStackList,stackItem);
    if(stackItem != NULL)
    {
        if(!QFile::exists(stackItem))
        {
            return;
        }
        else
        {
//save the current operation
            qDebug()<<originalFilePath<<currentFilePath<<stackItem;

            if(QFile::exists(originalFilePath))
            {
                QFile::remove(originalFilePath);
            }
            QFile::copy(stackItem,originalFilePath);
//            QFile fileSaved(stackItem);
//            fileSaved.copy(originalFilePath);
        }
    }
}

/*picture editor go back to the original picture*/
void MainPage::slot_reset()
{
    struct stackList *tmpList = fileStackList;
    QString stackItem = NULL;
    while(tmpList->top->flag == 1)
    {
        tmpList->top = tmpList->top->next;
        tmpList->num--;
    }
    stackListGetTop(tmpList,stackItem);

    qDebug()<<stackItem;
    if(stackItem != NULL)
    {
        QFile tempFile(stackItem);
        if(!tempFile.exists())
        {
            return;
        }
        else
        {
            currentFilePath = stackItem;
            this->pictureView->setPixmapOnView(stackItem);
            sig_openFile(stackItem);
        }
    }
    topMenuBar->btnUndo->setEnabled(false);
    topMenuBar->btnRedo->setEnabled(false);
}

/*this is a redo function*/
void MainPage::slot_redo()
{
    if(stackListIsEmpty(redoStackList))
    {
        return ;
    }
    QString stackItem = NULL;
    stackListPop(redoStackList,stackItem);
    stackListPush(fileStackList,stackItem,1);
    if(stackItem != NULL)
    {
        QFile tempfile(stackItem);
        if(!tempfile.exists())
        {
            return;
        }
        else
        {
            currentFilePath = stackItem;
            this->pictureView->setPixmapOnView(stackItem);
            sig_openFile(stackItem);
        }
    }

    topMenuBar->btnRedo->setEnabled(!stackListIsEmpty(redoStackList));
    topMenuBar->btnUndo->setEnabled(!stackListIsEmpty(fileStackList));
}

/*this is a undo function*/
void MainPage::slot_undo()
{
    qDebug()<<"slot_undo";
    if(stackListIsEmpty(fileStackList) /*|| (1 == stackListGetSizeOf(fileStackList))*/)
    {
        return;
    }
//load the previous path
    QString stackItem=NULL;
    stackListPop(fileStackList,stackItem);
    stackListPush(redoStackList,stackItem,1);
    if(stackItem == this->lastOperation)
    {
        stackListPop(fileStackList,stackItem);
        stackListPush(redoStackList,stackItem,1);
    }

    if(stackItem != NULL)
    {

/*juge the temp file exist or not*/
        QFile tempfile(stackItem);
        if(!tempfile.exists())
        {
            return ;
        }
        else
        {
/*load the previous operation*/
            currentFilePath=stackItem;
            pictureView->setPixmapOnView(stackItem);
            sig_openFile(stackItem);
        }
    }

    topMenuBar->btnRedo->setEnabled(!stackListIsEmpty(redoStackList));
    topMenuBar->btnUndo->setEnabled(!stackListIsEmpty(fileStackList));
}

void MainPage::slot_w800()
{
//    qDebug()<<"slot_w800";
    this->modelChangeSize(800,600);
}
void MainPage::slot_w1200()
{
//    qDebug()<<"slot_w1200";
    this->modelChangeSize(1200,900);
}
void MainPage::slot_w1600()
{
//    qDebug()<<"slot_w1600";
    this->modelChangeSize(1600,1200);
}
void MainPage::slot_freeAdjustSize()
{

    freeCutDialog=new AdjustSizeDialog(this);
    freeCutDialog->show();
    connect(freeCutDialog->okBtn,SIGNAL(clicked()),this,SLOT(freeAdjustSizeCallback()));
//    qDebug()<<"slot_freeAdjustSize";
}
void MainPage::freeAdjustSizeCallback()
{
    bool ok;
    this->modelChangeSize(this->freeCutDialog->wInput->text().toInt(&ok,10),
                          this->freeCutDialog->hInput->text().toInt(&ok,10));
    this->freeCutDialog->close();
}


 QString MainPage::savePixFile(QPixmap &pix)
 {
     /*check the configure DIR*/
     QDir*proDir = new QDir;
     bool exist = proDir->exists(QDir::homePath()+"/.local/nfspb/tmp");
     if(!exist)
     {
         proDir->mkdir(QDir::homePath()+"/.local/nfspb/tmp");
     }
     /*tempfile name*/
     QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-ms");
     QString picPath=QDir::homePath()+"/.local/nfspb/tmp/"+filename+".png";
     pix.save(picPath.toStdString().c_str(),"png");

     return picPath;
 }

void MainPage::modelChangeSize(int width, int height)
{
    this->pictureView->currentCvMat.copyTo(tempImage);
    if(tempImage.empty())
    {
        qDebug()<<"obtain image failure";
        return;
    }

    Mat MatImg;
    cv::resize(tempImage,MatImg,cv::Size(width,height),0,0,CV_INTER_LINEAR);
    MatImg.copyTo(this->pictureView->currentCvMat);

    QPixmap pix=QPixmap::fromImage(Mat2QImage(this->pictureView->currentCvMat));

    QString picPath = savePixFile(pix);

    startPush(fileStackList,picPath,1);
/*load the temp file to show changed image*/
    currentFilePath=picPath;
    pictureView->setPixmapOnView(picPath);
    sig_openFile(picPath);
}

 void MainPage::modelCutApi(int x, int y, int width, int height)
 {

     QPixmap pix=this->pictureView->scaledPix.copy(x,y,width,height);

     QString picPath = savePixFile(pix);
     currentFilePath=picPath;
     pictureView->setPixmapOnView(picPath);
     sig_openFile(picPath);
     startPush(fileStackList,picPath,1);
 }
void MainPage::slot_finishedCutting()
{
//    qDebug()<<"slot_finishedCutting";
    if(cutFlag)
    {
        QPixmap pix=this->pictureView->scaledPix.copy(this->pdialog->getShotGeometry());

        QString picPath = savePixFile(pix);

        cutFlag=false;
        delete pdialog;
        pdialog=NULL;

        currentFilePath=picPath;
        pictureView->setPixmapOnView(picPath);
/*save the temp file(operation) to a stack list*/
        startPush(fileStackList,picPath,1);

    }
}
void MainPage::slot_pictureCut()
{
//    qDebug()<<"slot_pictureCut";
    this->modelCutApi(146,0,524,524);
}

void MainPage::slot_normalWallCut()
{   
    this->modelCutApi(73,0,670,524);
}

void MainPage::slot_wideWallCut()
{
//    qDebug()<<"slot_wideWallCut";
    this->modelCutApi(0,32,816,459);
}
void MainPage::slot_inch1Cut()
{
    this->modelCutApi(277,79,262,366);
}
void MainPage::slot_inch2Cut()
{
//    qDebug()<<"slot_inch2Cut";
    this->modelCutApi(274,40,267,404);
}


void MainPage::slot_freeCutting()
{
    qDebug()<<"free cutting event";

   if(!cutFlag)
   {
        pdialog= new PictureShotDialog(pictureView);
//        connect(pdialog->dialog,SIGNAL(sig_finishCut()),this,SLOT(slot_finishedCutting()));
        connect(pdialog,SIGNAL(sig_doubleClick()),this,SLOT(slot_finishedCutting()));
        pdialog->show();
        cutFlag=true;
   }
   else
   {
       return ;
   }
}

int MainPage::startPush(StackList*ps,QString &pItem,int flag)
{
/*initial parameter*/
    if(flag)
    {
        topMenuBar->btnUndo->setEnabled(true);
        topMenuBar->btnRedo->setEnabled(true);
        topMenuBar->btnReset->setEnabled(true);
        topMenuBar->btnCompare->setEnabled(true);
    }
    else
    {
//        topMenuBar->btnStoreAction->setEnabled(false);
        if(!stackListIsEmpty(ps))
        {
            stackListClear(ps);
        }

        topMenuBar->btnUndo->setEnabled(false);
        topMenuBar->btnRedo->setEnabled(false);
        topMenuBar->btnReset->setEnabled(false);
        topMenuBar->btnCompare->setEnabled(false);

    }
    stackListPush(ps,pItem,flag);
    lastOperation = pItem;
    return 0;
}

void MainPage::slot_receivePictureFileName(const QString&fileFullPath)
{
        originalFilePath = fileFullPath;
        currentFilePath=fileFullPath;
        pictureView->setPixmapOnView(fileFullPath);
/*keep the new picture to the stacklist*/
        startPush(fileStackList,currentFilePath,0);
}


void MainPage::rotateImage(double angle,double scale)
{
    this->pictureView->currentCvMat.copyTo(tempImage);
    if(tempImage.empty())
    {
        qDebug()<<"obtain image failure";
        return;
    }
    Point2f center=Point2f(tempImage.cols/2,tempImage.rows/2);
//    double angle = 90;  // 旋转角度
//    double scale = 1.0; // 缩放尺度
    Mat rotateMat;
    rotateMat=getRotationMatrix2D(center,angle,scale);
    Mat rotateImg;
    warpAffine(tempImage,rotateImg,rotateMat,tempImage.size());

    rotateImg.copyTo(this->pictureView->currentCvMat);

    this->pictureView->imgCurrentHeight=this->pictureView->imgOriginalHeight;
    this->pictureView->imgCurrentWidth=this->pictureView->imgOriginalWidth;

    this->pictureView->pixMap=QPixmap::fromImage(Mat2QImage(this->pictureView->currentCvMat));

//save the pix to a temp file
    QString picPath = savePixFile(this->pictureView->pixMap);
    startPush(fileStackList,picPath,1);

    this->pictureView->updateCurrentImage();


}


//basic setting about rotate signal
void MainPage::slot_rotateLeftCvPicture()
{

//qt function
//    pictureView->rotateImage(-90);

    /*opencv function*/
    this->rotateImage(90,1.0);

}
void MainPage::slot_rotateRightCvPicture()
{
//    pictureView->rotateImage(90);
    this->rotateImage(-90,1.0);
}

 /*up and down*/
void MainPage::slot_rotateFrontCvPicture()
{
    cv::Mat dst;
    this->pictureView->currentCvMat.copyTo(tempImage);
    CV_Assert(tempImage.depth() == CV_8U);
    dst.create(tempImage.rows, tempImage.cols, tempImage.type());

    int rows = tempImage.rows;
    int cols = tempImage.cols;

    switch (tempImage.channels())
    {
    case 1:
        const uchar *origal;
        uchar *p;
        for (int i = 0; i < rows; i++){
            origal = tempImage.ptr<uchar>(i);
            p = dst.ptr<uchar>(i);
            for (int j = 0; j < cols; j++){
                p[j] = origal[cols - 1 - j];
            }
        }
        break;
    case 3:
        const Vec3b *origal3;
        Vec3b *p3;
        for (int i = 0; i < rows; i++) {
            origal3 = tempImage.ptr<Vec3b>(i);
            p3 = dst.ptr<Vec3b>(i);
            for(int j = 0; j < cols; j++){
                p3[j] = origal3[cols - 1 - j];
            }
        }
        break;
    default:
        break;
    }
    dst.copyTo(this->pictureView->currentCvMat);

    this->pictureView->imgCurrentHeight=this->pictureView->imgOriginalHeight;
    this->pictureView->imgCurrentWidth=this->pictureView->imgOriginalWidth;

    this->pictureView->pixMap=QPixmap::fromImage(Mat2QImage(this->pictureView->currentCvMat));

    QString picPath = savePixFile(this->pictureView->pixMap);
    startPush(fileStackList,picPath,1);

    this->pictureView->updateCurrentImage();

}

/*right and left*/
void MainPage::slot_rotateBackCvPicture()
{
    this->pictureView->currentCvMat.copyTo(this->tempImage);
    cv::Mat dst;

    CV_Assert(tempImage.depth() == CV_8U);
    dst.create(tempImage.rows, tempImage.cols, tempImage.type());

    int rows = tempImage.rows;

    for (int i = 0; i < rows; i++)
    {
       tempImage.row(rows - i - 1).copyTo(dst.row(i));
    }
    dst.copyTo(this->pictureView->currentCvMat);

    this->pictureView->imgCurrentHeight=this->pictureView->imgOriginalHeight;
    this->pictureView->imgCurrentWidth=this->pictureView->imgOriginalWidth;

    this->pictureView->pixMap=QPixmap::fromImage(Mat2QImage(this->pictureView->currentCvMat));

    QString picPath = savePixFile(this->pictureView->pixMap);
    startPush(fileStackList,picPath,1);

    this->pictureView->updateCurrentImage();

}

void MainPage::slot_narrowCurrentImage()
{
    this->rotateImage(0,0.944911);
}
void MainPage::slot_enlargeCurrentImage()
{
    this->rotateImage(0,1.058300);
}

//////////////////////////////////////////
/// Filter
///
//调节亮度
void MainPage::slot_BrightSlider(int pos_BrightSlider)
{   
    pictureFilter->getBright(pos_BrightSlider, pictureView);
    pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
    if(releaseFilterFlag)       //判断是否鼠标是否松开滑动条， 同时写入链表
    {
        QString picPath = savePixFile(pictureView->pixMap);
        startPush(fileStackList,picPath,1);
        releaseFilterFlag = false;
    }
}

//对比度调节
void MainPage::slot_ContrastSlider(int pos_ContrastSlider)
{
    pictureFilter->getContrast(pos_ContrastSlider, pictureView);
    pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));

    if(releaseFilterFlag)
    {
        QString picPath = savePixFile(pictureView->pixMap);
        startPush(fileStackList,picPath,1);
        releaseFilterFlag = false;
    }
}

//色彩饱和度调节
void MainPage::slot_colorSaturationSlider(int pos_colorSaturationSlider)
{
    pictureFilter->getColorSaturation(pos_colorSaturationSlider, pictureView);
    pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
    if(releaseFilterFlag)
    {
        QString picPath = savePixFile(pictureView->pixMap);
        startPush(fileStackList,picPath,1);
        releaseFilterFlag = false;
    }
}

//锐度调节
void MainPage::slot_resolutionSlider(int pos_resolutionSlider)
{
    pictureFilter->getResolution(pos_resolutionSlider, pictureView);
    pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
    if(releaseFilterFlag)
    {
        QString picPath = savePixFile(pictureView->pixMap);
        startPush(fileStackList,picPath,1);
        releaseFilterFlag = false;
    }
}

void MainPage::slot_sliderIsReleased()
{
    releaseFilterFlag = true;
}

//mosaic slots
void MainPage::slot_mouseIsReleased()
{
    releaseMosaicFlag = true;
}

void MainPage::slot_mouseEraserIsReleased()
{
    releaseMosaicEraserFlag = true;
}

void MainPage::slot_mosaicBrush()
{
    pictureMosaic = new PictureMosaic(pictureView);
    connect(pictureMosaic, SIGNAL(sig_drag(QMouseEvent *)), this, SLOT(slot_doMosaic(QMouseEvent *)));
    connect(pictureMosaic, SIGNAL(sig_mouseIsReleased()), this, SLOT(slot_mouseIsReleased()));
    pictureMosaic->pictureAndWidgetSize(pictureView);
    pictureMosaic->mouseDragBrush();
}

void MainPage::slot_doMosaic(QMouseEvent* event)
{
    int mosaicWidthHeight = 50;
//坐标转换函数
    QSizeF mosaicPoint = pictureMosaic->mousePointTransfer(event);
    bool rectFlag = pictureMosaic->setRectFlag(mosaicPoint, mosaicWidthHeight);
    pictureMosaic->doMosaic(mosaicPoint, pictureView, mosaicWidthHeight, rectFlag);
    if(releaseMosaicFlag)
    {
        pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
        QString picPath = savePixFile(pictureView->pixMap);
        startPush(fileStackList,picPath,1);
        releaseMosaicFlag = false;
    }
    isDoMosaicFlag = true;
}

void MainPage::slot_mosaicEraser()
{
    pictureMosaic = new PictureMosaic(pictureView);
    connect(pictureMosaic,SIGNAL(sig_drag(QMouseEvent *)),this,SLOT(slot_doEraser(QMouseEvent *)));
    connect(pictureMosaic, SIGNAL(sig_mouseIsReleased()), this, SLOT(slot_mouseEraserIsReleased()));
    pictureMosaic->pictureAndWidgetSize(pictureView);
    pictureMosaic->mouseDragEraser();
}

void MainPage::slot_doEraser(QMouseEvent* event)
{
    if(isDoMosaicFlag)
    {
        int mosaicWidthHeight = 50;
//坐标转换函数
        QSizeF mosaicPoint = pictureMosaic->mousePointTransfer(event);
        bool rectFlag = pictureMosaic->setRectFlag(mosaicPoint, mosaicWidthHeight);
        pictureMosaic->doEraser(mosaicPoint, pictureView, mosaicWidthHeight, rectFlag);
        if(releaseMosaicEraserFlag)
        {
            qDebug()<<"slot_doEraser";
            pictureView->pixMap=QPixmap::fromImage(Mat2QImage(pictureView->currentCvMat));
            QString picPath = savePixFile(pictureView->pixMap);
            startPush(fileStackList,picPath,1);
            releaseMosaicEraserFlag = false;
        }
    }
}

//formatConvert
void MainPage::slot_formatConvert()
{
    pictureFormatConvert->doThread(currentFilePath);
}

//ComparePage
void MainPage::slot_btnCompareIsPressed()
{
    QString stackItem = NULL;
    stackListGetTop(fileStackList, stackItem);
    emit sig_receiveCurrentImage(stackItem);
    emit sig_receiveFirstImage(originalFilePath);
}

//Puzzle
void MainPage::slot_templatePuzzlePress()
{
    QString stackItem = NULL;
    stackListGetTop(fileStackList, stackItem);
    emit sig_receiveFirstImg(stackItem);
}

void MainPage::slot_puzzle_1()
{
   this->pictureStackedWidget->picturePuzzle->stackedWidget->setCurrentIndex(0);
}

void MainPage::slot_puzzle_2()
{
    this->pictureStackedWidget->picturePuzzle->stackedWidget->setCurrentIndex(1);
}

void MainPage::slot_puzzle_3()
{
    this->pictureStackedWidget->picturePuzzle->stackedWidget->setCurrentIndex(2);
}

void MainPage::slot_puzzle_4()
{
    this->pictureStackedWidget->picturePuzzle->stackedWidget->setCurrentIndex(3);
}

void MainPage::slot_freePuzzlePress()
{

}

MainPage::~MainPage()
{

}

