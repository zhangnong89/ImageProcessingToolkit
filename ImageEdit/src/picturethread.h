#ifndef PICTURETHREAD_H
#define PICTURETHREAD_H
#include"all.h"

class PictureThread : public QThread
{

    Q_OBJECT

    void run()
    {
        qDebug()<<"Thread!";
        emit sig_pictureThread();
    }

signals:
    void sig_pictureThread();

};

#endif // PICTURETHREAD_H
