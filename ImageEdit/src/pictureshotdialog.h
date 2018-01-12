#ifndef PICTURESHOTDIALOG
#define PICTURESHOTDIALOG

#pragma once
#include "all.h"

#include "cutdialog.h"
#include <QRect>

class CutDialog;

class PictureShotDialog :public QWidget
{
    Q_OBJECT

public:
    explicit PictureShotDialog(QWidget *parent = 0);

    CutDialog *dialog;
    ~PictureShotDialog(void);    

    QRect getShotGeometry();

protected:
    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent*);

signals:
    void sig_doubleClick();
};



#endif // PICTURESHOTDIALOG

