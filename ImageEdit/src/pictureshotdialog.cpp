#include "pictureshotdialog.h"

PictureShotDialog::PictureShotDialog(QWidget *parent)
    :QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    dialog = new CutDialog(this);
    dialog->show();
    setGeometry(0,0,parentWidget()->width(),parentWidget()->height());
}


PictureShotDialog::~PictureShotDialog(void)
{

}

void PictureShotDialog::paintEvent(QPaintEvent *)
{

    QPainterPath painterPath;
    QPainterPath p;
    p.addRect(x(),y(),rect().width(),rect().height());
    painterPath.addRect(dialog->geometry());
    QPainterPath drawPath =p.subtracted(painterPath);

    QPainter paint(this);
    paint.setOpacity(0.7);
    paint.fillPath(drawPath,QBrush(Qt::black));
}

QRect PictureShotDialog::getShotGeometry()
{
    return dialog->geometry();
}

void PictureShotDialog::mouseDoubleClickEvent(QMouseEvent *)
{
    emit sig_doubleClick();
}
