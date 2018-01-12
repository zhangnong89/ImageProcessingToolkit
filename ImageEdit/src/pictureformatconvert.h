#ifndef PICTUREFORMATCONVERT
#define PICTUREFORMATCONVERT
#include"all.h"
class PictureView;
class PictureThread;
class PictureFormatConvert: public QWidget
{
    Q_OBJECT
public:
    PictureFormatConvert();
    ~PictureFormatConvert();
    void doThread(const QString& fileFullPath);
    PictureView *pictureView;
    QString fileFullPath;
    PictureThread* pictureThread;
    QString lineEditText;
    QString comboText;
signals:
    void sig_convertFinish();
    void sig_openFile(QString fileName);
public slots:
    void slot_convertFunc();
    void slot_convertGetText(QString&, QString&);
};

#endif // PICTUREFORMATCONVERT

