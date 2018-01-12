#include"topmenubar.h"
/*******************上部菜单栏************************/
TopMenuBar::TopMenuBar(QWidget *parent)
{
    Q_UNUSED(parent);
    setAutoFillBackground(true);
    setPalette(QColor(Qt::black));
    setFixedHeight(60);

    btnOpenFile = new QPushButton("");
    btnOpenFile->setStyleSheet("QPushButton{border-image:url(:/normalImages/openFile_normal.png);}"
                               "QPushButton:hover{border-image:url(:/normalImages/openFile_clicked.png);}"
                               "QPushButton:pressed{border-image:url(:/normalImages/openFile_clicked.png);}");
    btnOpenFile->setFixedHeight(40);
    btnOpenFile->setFixedWidth(118);
    btnOpenFile->setToolTip("打开新图片");

    btnSave = new QPushButton("");
    btnSave->setStyleSheet("QPushButton{border-image:url(:/normalImages/save_normal.png);}"
                           "QPushButton:hover{border-image:url(:/normalImages/save_focus.png);}"
                           "QPushButton:pressed{border-image:url(:/normalImages/save_clicked.png);}");
    btnSave->setFixedHeight(31);
    btnSave->setFixedWidth(70);
    btnSave->setToolTip("保存图片");

    btnSaveAs = new QPushButton("");
    btnSaveAs->setStyleSheet("QPushButton{border-image:url(:/normalImages/saveAs_normal.png);}"
                             "QPushButton:hover{border-image:url(:/normalImages/saveAs_focus.png);}"
                             "QPushButton:pressed{border-image:url(:/normalImages/saveAs_clicked.png);}");

    btnSaveAs->setFixedHeight(31);
    btnSaveAs->setFixedWidth(84);
    btnSaveAs->setToolTip("另存为");

    btnStoreAction = new QPushButton("");
    btnStoreAction->setStyleSheet("QPushButton{border-image:url(:/normalImages/storageAction_normal.png);}"
                                  "QPushButton:hover{border-image:url(:/normalImages/storageAction_focus.png);}"
                                  "QPushButton:pressed{border-image:url(:/normalImages/storageAction_clicked.png);}");
    btnStoreAction->setFixedHeight(31);
    btnStoreAction->setFixedWidth(98);
    btnStoreAction->setToolTip("保存动作");

    btnUndo = new QPushButton("");
    btnUndo->setStyleSheet("QPushButton{border-image:url(:/normalImages/undo_normal.png);}"
                           "QPushButton:hover{border-image:url(:/normalImages/undo_focus.png);}"
                           "QPushButton:pressed{border-image:url(:/normalImages/undo_clicked.png);}");
    btnUndo->setFixedHeight(31);
    btnUndo->setFixedWidth(70);
    btnUndo->setToolTip("撤销");

    btnRedo = new QPushButton("");
    btnRedo->setStyleSheet("QPushButton{border-image:url(:/normalImages/redo_normal.png);}"
                           "QPushButton:hover{border-image:url(:/normalImages/redo_focus.png);}"
                           "QPushButton:pressed{border-image:url(:/normalImages/redo_clicked.png);}");
    btnRedo->setFixedHeight(31);
    btnRedo->setFixedWidth(70);
    btnRedo->setToolTip("重做");

    btnReset = new QPushButton("");
    btnReset->setStyleSheet("QPushButton{border-image:url(:/normalImages/reset_normal.png);}"
                            "QPushButton:hover{border-image:url(:/normalImages/reset_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/normalImages/reset_clicked.png);}");
    btnReset->setFixedHeight(31);
    btnReset->setFixedWidth(70);
    btnReset->setToolTip("还原");

    btnCompare = new QPushButton("");
    btnCompare->setStyleSheet("QPushButton{border-image:url(:/normalImages/compare_normal.png);}"
                              "QPushButton:hover{border-image:url(:/normalImages/compare_focus.png);}"
                              "QPushButton:pressed{border-image:url(:/normalImages/compare_clicked.png);}");
    btnCompare->setFixedHeight(31);
    btnCompare->setFixedWidth(70);
    btnCompare->setToolTip("对比");
    btnAttribute = new QPushButton("");

    btnAttribute->setStyleSheet("QPushButton{border-image:url(:/normalImages/attribute_normal.png);}"
                                "QPushButton:hover{border-image:url(:/normalImages/attribute_focus.png);}"
                                "QPushButton:pressed{border-image:url(:/normalImages/attribute_clicked.png);}");
    btnAttribute->setFixedHeight(31);
    btnAttribute->setFixedWidth(70);
    btnAttribute->setToolTip("查看图片属性");
    this->picProperties = new pictureProperties(this);


    btnShare = new QPushButton("");
    btnShare->setStyleSheet("QPushButton{border-image:url(:/normalImages/share_normal.png);}"
                            "QPushButton:hover{border-image:url(:/normalImages/share_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/normalImages/share_clicked.png);}");
    btnShare->setFixedHeight(31);
    btnShare->setFixedWidth(70);
    btnShare->setToolTip("分享");

    QHBoxLayout *topMenuHbox = new QHBoxLayout;
    topMenuHbox->setContentsMargins(10, 0, 5, 0);
    topMenuHbox->setSpacing(0);

    topMenuHbox->addWidget(btnOpenFile);
    topMenuHbox->addSpacing(30);
    topMenuHbox->addWidget(btnSave);
    topMenuHbox->addWidget(btnSaveAs);
    topMenuHbox->addStretch();

    topMenuHbox->addWidget(btnStoreAction);
    topMenuHbox->addWidget(btnUndo);
    topMenuHbox->addWidget(btnRedo);
    topMenuHbox->addWidget(btnReset);
    topMenuHbox->addWidget(btnCompare);
    topMenuHbox->addWidget(btnAttribute);
    topMenuHbox->addWidget(btnShare);

    setLayout(topMenuHbox);
//set connection
    connect(btnOpenFile, SIGNAL(clicked()), this, SLOT(slot_OpenfileDialog()));
    connect(btnAttribute,SIGNAL(clicked()),this,SLOT(slot_attributeDialog()));

//    this->setStyleSheet("color: blue; background-color: red");
}

TopMenuBar::~TopMenuBar(){}
void TopMenuBar::slot_initialFile(QString fileName)
{
    this->currentFileName=fileName;
}

void TopMenuBar::slot_attributeDialog()
{
    cellItem = new CellItem(currentFileName,this);
    picProperties->updateData(cellItem);
    picProperties->show();
}
QString TopMenuBar::openFileDialog(QWidget *_parent, const QString defaultDir)
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

void TopMenuBar::slot_OpenfileDialog()
{
    QString tempDir;
    tempDir=QDir::homePath();
    tempDir.append("/图片");//set picture to be the default DIR
    QString fileName = openFileDialog(this, tempDir);
    currentFileName=fileName;
 //obtain the selected file full path
    if(!fileName.isEmpty())
    {
        sig_openFile(fileName);
        sig_initSlider();
    }
}

void TopMenuBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#414141"));
    painter.drawRect(rect());
}
