#ifndef PICTUREGRAPHICSITEM
#define PICTUREGRAPHICSITEM
#include "all.h"


class PictureGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    PictureGraphicsItem(const int &imgWidth,const int &imgHeigth,const QPixmap &pixmap,QGraphicsItem *parent = 0);
    bool isZoomed;
    bool isFitWindow;
    QSize imgSize;


    ~PictureGraphicsItem()
    {}

    const QPixmap &getPixmap()
    {
        return pix;
    }

QRectF boundingRect() const;
void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
virtual void dragEnterEvent(QGraphicsSceneDragDropEvent * e);
void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
void mousePressEvent(QGraphicsSceneMouseEvent* event);
void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    int imageWidth;
    int imageHeigth;
    QPixmap pix;
};



#endif // PICTUREGRAPHICSITEM

