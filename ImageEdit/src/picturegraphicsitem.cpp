#include"picturegraphicsitem.h"

PictureGraphicsItem::PictureGraphicsItem(const int &imgWidth,const int &imgHeigth,const QPixmap &pixmap,QGraphicsItem *parent )
    :QGraphicsItem(parent)
{
    isZoomed = false;
    isFitWindow = true;
    setAcceptDrops(false);
    setZValue(0);
    imageWidth = imgWidth;
    imageHeigth = imgHeigth;
    pix = pixmap;
}


QRectF PictureGraphicsItem::boundingRect() const
{
     return QRectF(QRectF(-imageWidth/2, -imageHeigth/2, imageWidth, imageHeigth));
}

void PictureGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-imageWidth/2, -imageHeigth/2, imageWidth, imageHeigth, pix);
}

 void PictureGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent * e)
{
    e->acceptProposedAction();
}


 void PictureGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
 {
//    QGraphicsView::mouseMoveEvent(event);
     if ((event->buttons() & Qt::LeftButton) /*&& isPressed && isZoom*/)
     {
//         this->move(event->globalPos() - this->differPos);
     }

 }

 void PictureGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
     if(event->button() == Qt::LeftButton)
     {
         this->setCursor(Qt::OpenHandCursor);
//         isPressed = true;
     }
 }

 void PictureGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton /*&& isPressed*/)
     {
//         isPressed = false;
//         this->setCursor(Qt::ArrowCursor);
     }
 }
