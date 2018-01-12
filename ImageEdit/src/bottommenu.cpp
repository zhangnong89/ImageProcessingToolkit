/*******************底部菜单栏************************/
#include"bottommenu.h"
BottomMenuBar::BottomMenuBar(QWidget *parent)
{
    Q_UNUSED(parent);
    setAutoFillBackground(true);
    setPalette(QColor(Qt::white));
    setFixedHeight(40);

    picInfo = new QPushButton("图片信息", this);
    picInfo->setToolTip("显示图片详细信息");
    picInfo->setFlat(true);
//    picInfo->setFixedWidth(100);
    sizeLbl = new QLabel("", this);
    sizeLbl->setAlignment(Qt::AlignCenter);
    sizeLbl->adjustSize();
    sizeLbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    btnPrevious = new QPushButton("");
    btnPrevious->setStyleSheet("QPushButton{border-image:url(:/normalImages/lastPic_normal.png);}"
                               "QPushButton:hover{border-image:url(:/normalImages/lastPic_focus.png);}"
                               "QPushButton:pressed{border-image:url(:/normalImages/lastPic_clicked.png);}");
    btnPrevious->setFixedWidth(28);
    btnPrevious->setFixedHeight(26);
    btnNext = new QPushButton("");
    btnNext->setStyleSheet("QPushButton{border-image:url(:/normalImages/nextPic_normal.png);}"
                           "QPushButton:hover{border-image:url(:/normalImages/nextPic_focus.png);}"
                           "QPushButton:pressed{border-image:url(:/normalImages/nextPic_clicked.png);}"
                           );
    btnNext->setFixedWidth(28);
    btnNext->setFixedHeight(26);
    btnRemove = new QPushButton("");
    btnRemove->setStyleSheet("QPushButton{border-image:url(:/normalImages/delete_normal.png);}"
                             "QPushButton:hover{border-image:url(:/normalImages/delete_focus.png);}"
                             "QPushButton:pressed{border-image:url(:/normalImages/delete_clicked.png);}"
                             );
    btnRemove->setFixedWidth(28);
    btnRemove->setFixedHeight(26);


    btnFullScreen = new QPushButton("");
    btnFullScreen->setStyleSheet("QPushButton{border-image:url(:/normalImages/fullscreen_normal.png);}"
                                 "QPushButton:hover{border-image:url(:/normalImages/fullscreen_focus.png);}"
                                 "QPushButton:pressed{border-image:url(:/normalImages/fullscreen_clicked.png);}");
    btnFullScreen->setFixedWidth(70);
    btnFullScreen->setFixedHeight(26);

    btnFitScreen = new QPushButton("");
    btnFitScreen->setStyleSheet("QPushButton{border-image:url(:/normalImages/fitScreen_normal.png);}"
                                "QPushButton:hover{border-image:url(:/normalImages/fitScreen_focus.png);}"
                                "QPushButton:pressed{border-image:url(:/normalImages/fitScreen_clicked.png);}");
    btnFitScreen->setFixedWidth(70);
    btnFitScreen->setFixedHeight(26);
    btnOriginalSize = new QPushButton("");
    btnOriginalSize->setStyleSheet("QPushButton{border-image:url(:/normalImages/original_normal.png);}"
                                   "QPushButton:hover{border-image:url(:/normalImages/original_focus.png);}"
                                   "QPushButton:pressed{border-image:url(:/normalImages/original_clicked.png);}");
    btnOriginalSize->setFixedWidth(70);
    btnOriginalSize->setFixedHeight(26);





    QHBoxLayout *btmHbox = new QHBoxLayout;
    btmHbox->setContentsMargins(0,0,0,0);

//    btmHbox->setMargin(0);
    btmHbox->setSpacing(0);
    btmHbox->addSpacing(21);
    btmHbox->addWidget(btnPrevious);
    btmHbox->addSpacing(12);
    btmHbox->addWidget(btnNext);
    btmHbox->addSpacing(6);
    btmHbox->addWidget(btnRemove);
//    btmHbox->setSpacing(254);

    btmHbox->addStretch();
    btmHbox->addWidget(picInfo);
    btmHbox->addWidget(sizeLbl);

    btmHbox->addStretch();
    btmHbox->addWidget(btnFullScreen);
    btmHbox->addWidget(btnFitScreen);
    btmHbox->addWidget(btnOriginalSize);

//    leftHbox->addStretch();
//    btmHbox->addWidget(btnPrevious);
//    btmHbox->addWidget(btnNext);
//    btmHbox->addWidget(btnRemove);
//    leftHbox->addStretch();


    QWidget *leftWiget = new QWidget;
    leftWiget->setLayout(btmHbox);


    connect(picInfo, SIGNAL(clicked()), this, SLOT(picInfoCallbackFunc()));

    /*****************制作滑动条*********************/
    picSlider = new QSlider(Qt::Horizontal);
    picSlider->setFixedWidth(180);
    picSlider->setRange(0, 100);
    picSlider->setValue(50);

    picNarrow = new QPushButton("-");
    picNarrow->setFixedSize(16, 16);
    picEnlarge = new QPushButton("+");
    picEnlarge->setFixedSize(16, 16);

    picBottomRightHbox = new QHBoxLayout;
    picBottomRightHbox->setContentsMargins(0,0,0,0);
    picBottomRightHbox->setSpacing(0);
    picBottomRightHbox->addStretch();
    picBottomRightHbox->addWidget(picNarrow);
    picBottomRightHbox->addWidget(picSlider);
    picBottomRightHbox->addWidget(picEnlarge);
    picBottomRightHbox->addStretch();

    QWidget *rightWiget = new QWidget;
    rightWiget->setFixedWidth(SIDEMENUBAR_W);
    rightWiget->setLayout(picBottomRightHbox);
    /*********************end*********************/

    QHBoxLayout *t_1_hl = new QHBoxLayout;
    t_1_hl->setContentsMargins(0,0,0,0);
    t_1_hl->setSpacing(0);
    t_1_hl->addWidget(leftWiget);
    t_1_hl->addWidget(rightWiget);

    setLayout(t_1_hl);

    picProperties=new pictureProperties(this);

    picSliderValue = 50;
    connect(this->picNarrow, SIGNAL(clicked()), this, SLOT(slot_picNarrow()));
    connect(this->picEnlarge, SIGNAL(clicked()), this, SLOT(slot_picEnlarge()));
    connect(this->picSlider, SIGNAL(valueChanged(int)), this, SLOT(slot_picSliderEvent(int)));

}

void BottomMenuBar::picInfoCallbackFunc()
{
     cellItem=new CellItem(currentFileName,this);
     picProperties->updateData(cellItem);
     picProperties->show();
}

void BottomMenuBar::updateSizeLabel(QString fileName)
{
    QImageReader imageReader(fileName);
//    sizeLbl = new QLabel("尺寸：123×345", this);
    sizeLbl->setText("尺寸："+QString::number(imageReader.size().width())+" x "+QString::number(imageReader.size().height()));
}
void BottomMenuBar::enablePicInfoCallbackFunc(QString fileName)
{
    currentFileName=fileName;
//    this->picInfo->setEnabled(true);

    this->show();
    updateSizeLabel(fileName);
//    picProperties->updateData();
}

void BottomMenuBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#f8f8f8"));
    painter.drawRect(rect());
}

void BottomMenuBar::slot_picNarrow()
{
    emit sig_picAdjustSize(false);
}

void BottomMenuBar::slot_picEnlarge()
{
    emit sig_picAdjustSize(true);
}

void BottomMenuBar::slot_picSliderEvent(int para_sliderValue)
{
    if(para_sliderValue<picSliderValue)
        emit sig_picAdjustSize(false);
    else
        emit sig_picAdjustSize(true);

    picSliderValue = para_sliderValue;
}

BottomMenuBar::~BottomMenuBar()
{

}
