#include "initpage.h"


InitPage::InitPage(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::gray));

    QPushButton *openFileBtn = new QPushButton("打开文件");
    openFileBtn->setFixedSize(120, 55);
//    connect(t_openFileBtn, SIGNAL(clicked()), this, SIGNAL(sig_openFile()));
    connect(openFileBtn, SIGNAL(clicked()), this, SLOT(slot_OpenfileDialog()));

    QVBoxLayout *t_1_vl = new QVBoxLayout;
    t_1_vl->addStretch(4);
    t_1_vl->addWidget(openFileBtn, 0, Qt::AlignHCenter);
    t_1_vl->addStretch(3);
    setLayout(t_1_vl);
}


QString InitPage::openFileDialog(QWidget *_parent, const QString defaultDir)
{
    QString tempDefaultDir;

    if(defaultDir.isNull())
    {
       tempDefaultDir  = QDir::homePath();//指定默认打开的路径
    }
    else
    {
        tempDefaultDir = defaultDir;
    }

    QString  selectedFile = QFileDialog::getOpenFileName(_parent,"打开图片",tempDefaultDir);//从默认打开的路径选择文件
    QStringList format;
    format << "bmp" << "gif" << "jpg" << "jpeg" << "png"
           << "pbm" << "pgm" << "ppm" << "xbm" << "xpm";

    if((QFileInfo(selectedFile).isFile())&&(selectedFile.trimmed()!=""))//判断是不是文件并且没有取消选择文件
    {

        QImageReader imageReader;
        QByteArray ba = imageReader.imageFormat(selectedFile);

        if(format.contains(ba))        //判断返回的的格式包含在格式列表中
            return selectedFile;
        else
        {
            QString message = "无法载入文件\""+selectedFile + "\"\n" +
                            "分析:图片文件损坏或非图片文件...";
            MessageBox t_msgBox(QString("取消"), QString("确定"),
                                  QString("覆盖图片"), false,
                                  QPixmap(":/prefix1/1-images/error.png"),
                                  message, _parent);
            t_msgBox.exec();
            return NULL;
        }
    }
    else
        return NULL;
}

void InitPage::slot_OpenfileDialog()
{
        QString tempDir;
        tempDir=QDir::homePath();
        tempDir.append("/图片");//set picture to be the default DIR
        QString t_fileName = openFileDialog(this, tempDir);
   //打开文件
   if(!t_fileName.isEmpty())
   {
       sig_openFile(t_fileName);
   }
}
InitPage::~InitPage()
{

}

