#ifndef PICTUREVIEW_H
#define PICTUREVIEW_H

#include"all.h"
//#include <QGraphicsItem>

class PictureGraphicsItem;
class BottomMenuBar;
class PictureView : public QGraphicsView
{
    Q_OBJECT

public:
    friend class PictureMosaic;
    friend class PictureFormatConvert;
    friend class PictureFilter;
    friend class PicturePuzzle;
    friend class mainpage;
     PictureView(const QString&currentFile,QWidget *parent = 0);
     QGraphicsScene *graphicsScene ;
     PictureGraphicsItem*pictureGraphicsItem;
     BottomMenuBar* bottomMenuBar;

     qreal imgOriginalWidth;           //原图宽
     qreal imgOriginalHeight;

     qreal imgCurrentWidth;
     qreal imgCurrentHeight;

    ~PictureView();
     QSize getImageSize(const QString &filename);
     void setPixmapOnView(const QString&fileName);
     void updateCurrentImage();

//     void updateCurrentCvPicture(const QString &fileName,const QImage &image);
     void fitWindow();
    QImage getCurrentImage();
    QImage recordCurrentImage(const QString &fileName);
    void rotateImage(int angle);

    /*opencv function*/
    void imageBackup();
    void undo();

    cv::Mat currentCvMat;
    cv::Mat previousCvMat;
    QPixmap pixMap;
    QPixmap scaledPix;

//    bool cutEventFlag;
    QPixmap getShotPix();

    void takePartShot();
    void startScreenShot();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

protected:
//    void showEvent(QShowEvent*event);
//    void keyPressEvent(QKeyEvent*event);

//    void mousePressEvent(QMouseEvent*event);
//    void mouseMoveEvent(QMouseEvent*event);
//    void mouseReleaseEvent(QMouseEvent*event);
//    void enterEvent(QEvent*event);

//    void paintEvent(QPaintEvent *);
//    void updateCurrentPaint();

private:
    QString currentFileFullPath;
    cv::Mat firstCvMat;

//     bool isDrawing;
     QPoint startPoint;
     QPoint endPonit;
     QRect shotRect;

     QPixmap pixmap_;//范围内的画面整体的捕捉
     QPixmap shotPix;
     qreal factor;

//Mouse Event
    bool isPressed;
    bool isZoom;
    QPoint lastPoint;
    QPoint windowPos;
    QPoint mousePos;
    QPoint differPos;
    qreal scaleFactor;   //图片缩放常数
    QMatrix old_matrix;

     QImage currentImage;
     QImage tempImage;

signals:
     void sig_mouseWheelZoom(bool);

public slots:
    void slot_zoom(bool);

};

#endif // PICTUREVIEW_H
