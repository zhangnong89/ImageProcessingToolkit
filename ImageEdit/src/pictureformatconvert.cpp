#include"pictureformatconvert.h"
PictureFormatConvert::PictureFormatConvert()
{ 

}

void PictureFormatConvert::slot_convertGetText(QString& eText, QString& cText)
{
    qDebug()<<"slot_convertGetText";
    lineEditText = eText;
    comboText = cText;
}

void PictureFormatConvert::doThread(const QString& fileFullPath)
{
//开启一个线程
    pictureView = new PictureView(fileFullPath);
    pictureThread = new PictureThread;
    connect(pictureThread, SIGNAL(sig_pictureThread()), this, SLOT(slot_convertFunc()));
    connect(pictureThread, SIGNAL(finished()), pictureThread, SLOT(deleteLater()));
    pictureThread->start();
}

void PictureFormatConvert::slot_convertFunc()
{
    qDebug()<<"slot_convertFunc";
    QProcess process;
     QStringList pictureList;
     QString pictureOld, pictureNew;
     QDir* picDir;
    pictureOld = pictureView->currentFileFullPath;
    pictureNew = lineEditText + "." + comboText;    //新文件命名
    pictureNew = picDir->homePath() + "/" + pictureNew;
    pictureList<<pictureOld<<pictureNew;
    process.execute("convert", pictureList);
    process.waitForFinished();
    sig_convertFinish();
}

PictureFormatConvert::~PictureFormatConvert()
{

}
