#include "pictureview.h"

PictureView::PictureView(const QString &currentFile,QWidget *parent):QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setResizeAnchor(AnchorViewCenter);
    setFocusPolicy(Qt::NoFocus);

//    cutEventFlag=false;
    currentFileFullPath=currentFile;
    QPixmap pix;
    QSize imageSize;
/*initial the loal parameter*/
//    currentImage.load(currentFileFullPath);

    imageSize=getImageSize(currentFileFullPath);
    pictureGraphicsItem= new PictureGraphicsItem(imageSize.width(),imageSize.height(),pix);
//    pictureGraphicsItem->setFlag(QGraphicsItem::ItemIsMovable,true);
    graphicsScene= new QGraphicsScene;
    setScene(graphicsScene);
    graphicsScene->addItem(pictureGraphicsItem);

    scaleFactor = 35;   //WheelEvent 图片缩放常数
    connect(this, SIGNAL(sig_mouseWheelZoom(bool)), this, SLOT(slot_zoom(bool)));
}

PictureView::~PictureView()
{

}
QSize PictureView::getImageSize(const QString &filename)
{
    QImageReader imgReader(filename);
    return imgReader.size();
}

//interface
void PictureView::setPixmapOnView(const QString &fileName)
{
    QSize imageSize;
    imageSize=getImageSize(fileName);
    imgCurrentWidth=imgOriginalWidth=imageSize.width();
    imgCurrentHeight=imgOriginalHeight=imageSize.height();

    currentFileFullPath=fileName;

    this->firstCvMat=cv::imread(fileName.toStdString());
    this->firstCvMat.copyTo(this->currentCvMat);
    imageBackup();

    pixMap=QPixmap::fromImage(Mat2QImage(currentCvMat));

//update the current picture in the itemview
    updateCurrentImage();
}

void PictureView::imageBackup()
{
    this->currentCvMat.copyTo(this->previousCvMat);
}

void PictureView::undo()
{
    if(this->previousCvMat.data !=0)
    {
        this->previousCvMat.copyTo(this->currentCvMat);
        pixMap=QPixmap::fromImage(Mat2QImage(currentCvMat));
        updateCurrentImage();
    }
}

void PictureView::updateCurrentImage()
{
    resetTransform();

//    pixMap=pixMap.scaled(pixMap.size(),Qt::KeepAspectRatio);
    if(pictureGraphicsItem != NULL) delete pictureGraphicsItem;
    if(graphicsScene != NULL) delete graphicsScene;

    pictureGraphicsItem = new PictureGraphicsItem(getImageSize(currentFileFullPath).width(),getImageSize(currentFileFullPath).height(),pixMap);


    graphicsScene = new QGraphicsScene;
//    pictureGraphicsItem->setFlag(QGraphicsItem::ItemIsMovable,true);
    graphicsScene->addItem(pictureGraphicsItem);
    setScene(graphicsScene);
//set the current picture fit the window
    this->fitWindow();
    this->scaledPix=this->pixMap.scaled(this->width(),this->height());
    graphicsScene->setBackgroundBrush(QColor(0, 0, 0));
}


//void PictureView::updateCurrentCvPicture(const QString &fileName, const QImage &image)
//{
//        currentImage=image;
//        QSize imageSize;
//        imageSize=getImageSize(fileName);
//        imgCurrentWidth=imgOriginalWidth=imageSize.width();
//        imgCurrentHeight=imgOriginalHeight=imageSize.height();
// /*update CV picture*/
//        resetTransform();
//        if(pictureGraphicsItem != NULL) delete pictureGraphicsItem;
//        if(graphicsScene != NULL) delete graphicsScene;
//        QPixmap pix;
//        pix.fromImage(image,Qt::AutoColor);

//        pictureGraphicsItem = new PictureGraphicsItem(imgCurrentWidth,imgCurrentHeight,pix);
//        graphicsScene = new QGraphicsScene;
//        graphicsScene->addItem(pictureGraphicsItem);
//        setScene(graphicsScene);

// /*set the current picture fit the window*/
//   fitWindow();
//}


void PictureView::fitWindow()
{

    if((this->width() > imgCurrentWidth) && (this->height() > imgCurrentHeight))
    {
        return;
    }

//adjust  size of the window
    if(imgCurrentHeight >imgOriginalHeight || imgCurrentWidth > imgOriginalWidth)
    {
        factor = imgOriginalWidth/imgCurrentWidth;
    }
    else
    {
        if(imgCurrentWidth/this->width() > imgCurrentHeight/this->height())
        {
            factor=this->width()/imgCurrentWidth;
        }
        else
        {
            factor=this->height()/imgCurrentHeight;
        }
    }
//set fit the current factor
        scale(factor,factor);
        imgCurrentHeight=imgCurrentHeight*factor;
        imgCurrentWidth=imgCurrentWidth*factor;
}

void PictureView::rotateImage(int angle)
{
//angle = 90 or angle =-90
    this->rotate(angle);

}

////////////////////////Mouse Event////////////////////////////
void PictureView::mouseMoveEvent(QMouseEvent *event)
{
//    QGraphicsView::mouseMoveEvent(event);
//    if ((event->buttons() & Qt::LeftButton) && isPressed && isZoom)
//    {
//        this->move(event->globalPos() - this->differPos);
//    }
}

void PictureView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->setCursor(Qt::OpenHandCursor	);
        isPressed = true;

        this->windowPos = this->pos();
        this->mousePos = event->globalPos();
        this->differPos = mousePos - windowPos;
    }
}

void PictureView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isPressed)
    {
        isPressed = false;
        this->setCursor(Qt::ArrowCursor);
    }
}

void PictureView::wheelEvent(QWheelEvent* event)
{
    if(event->delta()>0)
        emit sig_mouseWheelZoom(true);
    else
        emit sig_mouseWheelZoom(false);
}

void PictureView::slot_zoom(bool zoom)
{
    if (zoom && scaleFactor >= 0 && scaleFactor <=100)
    {
        scaleFactor += 10;
        old_matrix = this->matrix();
        this->resetMatrix();
        this->translate(old_matrix.dx(), old_matrix.dy());
        this->scale(scaleFactor/100.0, scaleFactor/100.0);
        qreal picWidth = this->width();
        qreal picHeight = this->height();
        picWidth = picWidth*scaleFactor/100;
        picHeight = picHeight*scaleFactor/100;
        isZoom = true;
    }
    else if (!zoom && scaleFactor >= 10)
    {
        scaleFactor -= 10;
        old_matrix = this->matrix();
        this->resetMatrix();
        this->translate(old_matrix.dx(), old_matrix.dy());
        this->scale(scaleFactor/100.0,  scaleFactor/100.0);
        isZoom = false;
    }
    else if (scaleFactor < 0)
    {
        scaleFactor = 0.0;
    }
}

#if 0

void PictureView::startScreenShot()
{
    this->pixmap_=this->pixMap;
    updateCurrentPaint();
//    repaint();
}
void PictureView::showEvent(QShowEvent *event)
{
    this->pixmap_=this->pixMap;
    if(cutEventFlag)
    {
        this->setCursor(Qt::CrossCursor);
    }
}

void PictureView::keyPressEvent(QKeyEvent *event)
{
    if(cutEventFlag)
    {
        if(event->key() == Qt::Key_Escape)
        {
            close();
        }
    }
}

void PictureView::enterEvent(QEvent*event)
{
    if(cutEventFlag)
    {
        this->setCursor(Qt::CrossCursor);
    }
}

void PictureView::mousePressEvent(QMouseEvent *event)
{
    if(cutEventFlag)
    {
/*record the start point*/
        startPoint = event->pos();
//        qDebug()<<"mousePressEvent01";
    }
}

void PictureView::mouseMoveEvent(QMouseEvent *event)
{
    if(cutEventFlag)
    {
/*record the end point and update the current pictureview*/
        endPonit = event->pos();
        this->updateCurrentPaint();
//        repaint();
    }
}


void PictureView::mouseReleaseEvent(QMouseEvent *event)
{
    if(cutEventFlag)
    {
/*record the end point and save the shot rect*/
        endPonit = event->pos();
//        qDebug()<<"mouseReleaseEvent01";
        this->takePartShot();

    }
}

void PictureView::takePartShot()
{
    if(startPoint.manhattanLength() > endPonit.manhattanLength())
    {
        qSwap(startPoint,endPonit);
    }
    shotPix = pixmap_.copy(QRect(startPoint,endPonit));
    cutEventFlag=false;
    setCursor(Qt::ArrowCursor);



/*save the current image*/
    QString filepath = "/home/jackey";
    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    filepath += "/";
    filepath += filename;
    filepath += ".png";
    shotPix.save(filepath);


//    pixMap=shotPix;
//    updateCurrentImage();

}

void PictureView::updateCurrentPaint()
//void PictureView::paintEvent(QPaintEvent*)
{   

    if(cutEventFlag)
    {
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
/*取得屏幕的大小*/
    QRect screenRect=this->rect();
/*把整体屏幕图像为自身描画*/
    painter.drawPixmap(screenRect,pixmap_);
/*稍微涂成圆角*/
    QPainterPath path;
    path.addRect(screenRect);
    path.addRoundedRect(QRect(startPoint,endPonit),8,8);

/*选择的范围之外的绘制抹黑*/
    painter.setBrush(QBrush(QColor(0,0,0,100)));
    painter.drawPath(path);
    }
}

QPixmap PictureView::getShotPix()
{
    return shotPix;
}

#endif
