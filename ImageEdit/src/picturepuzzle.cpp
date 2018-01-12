#include "picturepuzzle.h"
#include"QContextMenuEvent"

PicturePuzzle::PicturePuzzle(QWidget *parent)
    : QWidget(parent)
{
    pictureViewPuzzle1_1 = new PictureView(firstFilePath);
    pictureViewPuzzle1_2 = new PictureView(secondFilePath);
    pictureViewPuzzle2_1 = new PictureView(firstFilePath);
    pictureViewPuzzle2_2 = new PictureView(secondFilePath);
    pictureViewPuzzle3_1 = new PictureView(firstFilePath);
    pictureViewPuzzle3_2 = new PictureView(secondFilePath);
    pictureViewPuzzle4_1 = new PictureView(firstFilePath);
    pictureViewPuzzle4_2 = new PictureView(secondFilePath);

    combineWidget_1 = new CombineWidget_1(pictureViewPuzzle1_1, pictureViewPuzzle1_2);
    combineWidget_2 = new CombineWidget_2(pictureViewPuzzle2_1, pictureViewPuzzle2_2);
    combineWidget_3 = new CombineWidget_3(pictureViewPuzzle3_1, pictureViewPuzzle3_2);
    combineWidget_4 = new CombineWidget_4(pictureViewPuzzle4_1, pictureViewPuzzle4_2);
//图片区域不同的widget
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(combineWidget_1);
    stackedWidget->addWidget(combineWidget_2);
    stackedWidget->addWidget(combineWidget_3);
    stackedWidget->addWidget(combineWidget_4);

    QHBoxLayout* puzzleBox = new QHBoxLayout;
    puzzleBox->setMargin(0);
    puzzleBox->setSpacing(0);
    puzzleBox->addWidget(stackedWidget);
    this->setLayout(puzzleBox);

    menu = new QMenu();
    addImageAction = new QAction(this);
    saveImageAction =new QAction(this);
    addImageAction->setText("添加图片");
    saveImageAction->setText("保存");
    menu->addAction(addImageAction);
    menu->addAction(saveImageAction);

    connect(this->addImageAction, SIGNAL(triggered()), this, SLOT(slot_openFileDialog()));
    connect(this->saveImageAction, SIGNAL(triggered()), this, SLOT(slot_puzzle_save()));
    connect(this, SIGNAL(sig_receiveSecondImg(QString)), this, SLOT(slot_receiveSecondImg(QString)));
}

void PicturePuzzle::slot_receiveFirstImg(const QString &para_firstFilePath)
{
    firstFilePath = para_firstFilePath;
    pictureViewPuzzle1_1->setPixmapOnView(firstFilePath);
    pictureViewPuzzle2_1->setPixmapOnView(firstFilePath);
    pictureViewPuzzle3_1->setPixmapOnView(firstFilePath);
    pictureViewPuzzle4_1->setPixmapOnView(firstFilePath);
}

void PicturePuzzle::slot_receiveSecondImg(const QString &para_secondFilePath)
{
    secondFilePath = para_secondFilePath;
    pictureViewPuzzle1_2->setPixmapOnView(secondFilePath);
    pictureViewPuzzle2_2->setPixmapOnView(secondFilePath);
    pictureViewPuzzle3_2->setPixmapOnView(secondFilePath);
    pictureViewPuzzle4_2->setPixmapOnView(secondFilePath);
}

void PicturePuzzle::mousePressEvent(QMouseEvent *event)
{

}

void PicturePuzzle::mouseMoveEvent(QMouseEvent *event)
{

}

void PicturePuzzle::mouseReleaseEvent(QMouseEvent *event)
{

}

void PicturePuzzle::contextMenuEvent(QContextMenuEvent* event)
{
//菜单出现的位置为当前鼠标的位置
    menu->exec(QCursor::pos());
    event->accept();
}

QString PicturePuzzle::openFileDialog(QWidget *parent, const QString defaultDir)
{
    QString tempDefaultDir;
    if(defaultDir.isNull())
    {
        tempDefaultDir = QDir::homePath();
    }
    else
    {
        tempDefaultDir = defaultDir;
    }
    QString selectedFile =    QFileDialog::getOpenFileName(parent, "打开图片", tempDefaultDir);
    QStringList format;
    format<<"bmp"<<"gif"<<"jpg"<<"jpeg"<<"png"
                <<"pbm"<<"pgm"<<"ppm"<<"xbm"<<"xpm";
    if((QFileInfo(selectedFile).isFile())&&(selectedFile.trimmed()!=""))
    {
        QImageReader imageReader;
        QByteArray byteArray = imageReader.imageFormat(selectedFile);
        if(format.contains(byteArray))
            return selectedFile;
        else
        {
            QString message = "无法载入文件\"" + selectedFile + "\"\n" +
                             "分析:图片文件损坏或非图片文件...";
            MessageBox msgBox(QString("取消"), QString("确定"),
                              QString("覆盖图片"), false,
                              QPixmap(":/prefix1/1-images/error.png"),
                              message, parent);
            msgBox.exec();
            return NULL;
        }
    }
    else
        return NULL;
}

void PicturePuzzle::slot_openFileDialog()
{
    QString tempDir;
    tempDir=QDir::homePath();
    tempDir.append("/图片");//set picture to be the default DIR
    QString secondFilePath = openFileDialog(this, tempDir);
   //打开文件
    if(!secondFilePath.isEmpty())
    {
        emit sig_receiveSecondImg(secondFilePath);
    }
}

void PicturePuzzle::slot_puzzle_save()
{
    qDebug()<<"slot_puzzle_save";
    QDir* picDir;
    QPixmap grabPix;
    QString pictureNewPath;
    QDateTime* dateTime;
    QString current_date;
    qreal grabSizeWidth;
    qreal grabSizeHeight;
    QString fileName;

    grabSizeWidth = this->width();
    grabSizeHeight = this->height();
    grabPix = this->grab(QRect(QPoint(0, 0), QSize(grabSizeWidth, grabSizeHeight)));    //获取截图
    current_date = dateTime->currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    pictureNewPath = picDir->homePath() + "/" + current_date + "拼图" + ".jpg";
    fileName = QFileDialog::getSaveFileName(this,tr("保存"),pictureNewPath); //打开另存为窗口
    grabPix.save(fileName); //  保存图片
    emit sig_puzzle_saveSuccess();
}

PicturePuzzle::~PicturePuzzle()
{

}
