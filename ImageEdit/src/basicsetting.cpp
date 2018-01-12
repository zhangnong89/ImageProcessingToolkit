#include"basicsetting.h"
//基础设置页
BasicSetting::BasicSetting(QWidget *parent)
{
    Q_UNUSED(parent);
    setAutoFillBackground(true);
    setPalette(QColor(123, 123, 123));

    rotateBtn = new QPushButton("旋转");
    rotateBtn->setStyleSheet("color:white; font:14px;");
    cutBtn = new QPushButton("裁剪");
    cutBtn->setStyleSheet("color:white; font:14px;");
    sizeBtn = new QPushButton("尺寸");
    sizeBtn->setStyleSheet("color:white; font:14px;");

/**************rotate the current picture********************/


     rotateLeft = new QPushButton("");
     rotateLeft->setToolTip("向左转90度");
     rotateLeft->setStyleSheet("QPushButton{border-image:url(:/basicImages/rotate_left_normal.png);}"
                            "QPushButton:hover{border-image:url(:/basicImages/rotate_left_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/basicImages/rotate_left_clicked.png);}");
    rotateLeft->setFixedHeight(48);
    rotateLeft->setFixedWidth(72);

     rotateRight = new QPushButton("");
     rotateRight->setToolTip("向右转90度");
     rotateRight->setStyleSheet("QPushButton{border-image:url(:/basicImages/rotate_right_normal.png);}"
                                "QPushButton:hover{border-image:url(:/basicImages/rotate_right_focus.png);}"
                                "QPushButton:pressed{border-image:url(:/basicImages/rotate_right_clicked.png);}");
     rotateRight->setFixedHeight(48);
     rotateRight->setFixedWidth(72);

     rotateLR = new QPushButton("");
     rotateLR->setToolTip("左右翻转");
     rotateLR->setStyleSheet("QPushButton{border-image:url(:/basicImages/rotate_rightAndleft_normal.png);}"
                                "QPushButton:hover{border-image:url(:/basicImages/rotate_rightAndleft_focus.png);}"
                                "QPushButton:pressed{border-image:url(:/basicImages/rotate_rightAndleft_clicked.png);}");
     rotateLR->setFixedHeight(48);
     rotateLR->setFixedWidth(72);

     rotateUD = new QPushButton("");
     rotateUD->setToolTip("上下翻转");
     rotateUD->setStyleSheet("QPushButton{border-image:url(:/basicImages/rotate_upAnddown_normal.png);}"
                               "QPushButton:hover{border-image:url(:/basicImages/rotate_upAnddown_focus.png);}"
                               "QPushButton:pressed{border-image:url(:/basicImages/rotate_upAnddown_clicked.png);}");
     rotateUD->setFixedHeight(48);
     rotateUD->setFixedWidth(72);

    QVBoxLayout *qVbox1 = new QVBoxLayout;
    qVbox1->setSpacing(5);
    qVbox1->setContentsMargins(10, 10, 10, 10);
    qVbox1->addWidget(rotateLeft, 0, Qt::AlignLeft);
    qVbox1->addWidget(rotateRight, 0, Qt::AlignLeft);
    qVbox1->addWidget(rotateLR, 0, Qt::AlignLeft);
    qVbox1->addWidget(rotateUD, 0, Qt::AlignLeft);

    ButtonBox *btnBoxRotate = new ButtonBox;
    btnBoxRotate->hide();
    connect(rotateBtn, SIGNAL(clicked()), btnBoxRotate, SLOT(slot_showOrHide()));
    btnBoxRotate->setLayout(qVbox1);
//signal connection
    connect(rotateLeft,SIGNAL(clicked()),this,SIGNAL(sig_rotateLeft()));
    connect(rotateRight,SIGNAL(clicked()),this,SIGNAL(sig_rotateRight()));
    connect(rotateLR,SIGNAL(clicked()),this,SIGNAL(sig_rotateFront()));
    connect(rotateUD,SIGNAL(clicked()),this,SIGNAL(sig_rotateBack()));


/*******************************************************/


    freeCutting = new QPushButton("");
    freeCutting->setToolTip("自由裁剪");
    freeCutting->setFixedWidth(72);
    freeCutting->setFixedHeight(48);    
    freeCutting->setStyleSheet("QPushButton{border-image:url(:/basicImages/cut_free_normal.png);}"
                               "QPushButton:hover{border-image:url(:/basicImages/cut_free_focus.png);}"
                               "QPushButton:pressed{border-image:url(:/basicImages/cut_free_clicked.png);}");

    pictureCut = new QPushButton("头像尺寸");
    pictureCut->setToolTip("头像尺寸");
    pictureCut->setFixedWidth(72);
    pictureCut->setFixedHeight(40);
    pictureCut->setStyleSheet(
                                "QPushButton{color:white; font:14px;}"
                                "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                                "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                                "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}"
                              );

    normalWallCut = new QPushButton("标准壁纸");
    normalWallCut->setToolTip("标准壁纸");
    normalWallCut->setFixedWidth(72);
    normalWallCut->setFixedHeight(40);

    normalWallCut->setStyleSheet("QPushButton{color:white; font:14px;}"
                                 "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                                 "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                                 "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}");

    wideWallCut = new QPushButton("宽屏壁纸");
    wideWallCut->setToolTip("宽屏壁纸");
    wideWallCut->setFixedWidth(72);
    wideWallCut->setFixedHeight(40);
    wideWallCut->setStyleSheet("QPushButton{color:white; font:14px;}"
                               "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                               "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                               "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}");

    inch1Cut = new QPushButton("1寸证件照");
    inch1Cut->setToolTip("1寸证件照");
    inch1Cut->setFixedWidth(72);
    inch1Cut->setFixedHeight(40);
    inch1Cut->setStyleSheet("QPushButton{color:white; font:14px;}"
                            "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                            "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}");

    inch2Cut = new QPushButton("2寸证件照");
    inch2Cut->setToolTip("2寸证件照");
    inch2Cut->setFixedWidth(72);
    inch2Cut->setFixedHeight(40);
    inch2Cut->setStyleSheet("QPushButton{color:white; font:14px;}"
                            "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                            "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}");


    QVBoxLayout *qVbox2 = new QVBoxLayout;
    qVbox2->setSpacing(5);
    qVbox2->setContentsMargins(10, 10, 10, 10);
    qVbox2->addWidget(freeCutting, 0, Qt::AlignLeft);
    qVbox2->addWidget(pictureCut, 0, Qt::AlignLeft);
    qVbox2->addWidget(normalWallCut, 0, Qt::AlignLeft);
    qVbox2->addWidget(wideWallCut, 0, Qt::AlignLeft);
    qVbox2->addWidget(inch1Cut, 0, Qt::AlignLeft);
    qVbox2->addWidget(inch2Cut, 0, Qt::AlignLeft);

//signal connection
    connect(freeCutting,SIGNAL(clicked()),this,SIGNAL(sig_freeCutting()));
    connect(pictureCut,SIGNAL(clicked()),this,SIGNAL(sig_pictureCut()));
    connect(normalWallCut,SIGNAL(clicked()),this,SIGNAL(sig_normalWallCut()));
    connect(wideWallCut,SIGNAL(clicked()),this,SIGNAL(sig_wideWallCut()));
    connect(inch1Cut,SIGNAL(clicked()),this,SIGNAL(sig_inch1Cut()));
    connect(inch2Cut,SIGNAL(clicked()),this,SIGNAL(sig_inch2Cut()));

    ButtonBox *btnBoxCut = new ButtonBox;
    btnBoxCut->hide();
    connect(cutBtn, SIGNAL(clicked()), btnBoxCut, SLOT(slot_showOrHide()));
    btnBoxCut->setLayout(qVbox2);

/********************************************************/

    freeAdjustSize = new QPushButton("");
    freeAdjustSize->setToolTip("自由调节尺寸");
    freeAdjustSize->setStyleSheet("QPushButton{border-image:url(:/basicImages/size_free_normal.png);}"
                                  "QPushButton:hover{border-image:url(:/basicImages/size_free_focus.png);}"
                                  "QPushButton:pressed{border-image:url(:/basicImages/size_free_clicked.png);}");
    freeAdjustSize->setFixedWidth(72);
    freeAdjustSize->setFixedHeight(48);

    w800=new QPushButton("[800] x 600");
    w800->setToolTip("[1200] x 900");
    w800->setFixedWidth(75);
    w800->setFixedHeight(40);
    w800->setStyleSheet("QPushButton{color:white; font:12px;}"
                            "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                            "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}");

    w1200=new QPushButton("[1200] x 900");
    w1200->setToolTip("[1200] x 900");
    w1200->setFixedWidth(75);
    w1200->setFixedHeight(40);
    w1200->setStyleSheet("QPushButton{color:white; font:12px;}"
                            "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                            "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}");

    w1600=new QPushButton("[1600] x 1200");
    w1600->setToolTip("[1600] x 1200");
    w1600->setFixedWidth(75);
    w1600->setFixedHeight(40);
    w1600->setStyleSheet("QPushButton{color:white; font:12px;}"
                            "QPushButton{border-image:url(:/basicImages/background_normal.png);}"
                            "QPushButton:hover{border-image:url(:/basicImages/background_focus.png);}"
                            "QPushButton:pressed{border-image:url(:/basicImages/background_clicked.png);}");


    QVBoxLayout *qVbox3 = new QVBoxLayout;
    qVbox3->setSpacing(5);
    qVbox3->setContentsMargins(10, 10, 10, 10);
    qVbox3->addWidget(freeAdjustSize, 0, Qt::AlignLeft);
    qVbox3->addWidget(w800,0,Qt::AlignLeft);
    qVbox3->addWidget(w1200,0,Qt::AlignLeft);
    qVbox3->addWidget(w1600,0,Qt::AlignLeft);

    connect(freeAdjustSize,SIGNAL(clicked()),this,SIGNAL(sig_freeAdjustSize()));
    connect(w800,SIGNAL(clicked()),this,SIGNAL(sig_w800()));
    connect(w1200,SIGNAL(clicked()),this,SIGNAL(sig_w1200()));
    connect(w1600,SIGNAL(clicked()),this,SIGNAL(sig_w1600()));

    ButtonBox *btnBoxSize = new ButtonBox;
    btnBoxSize->hide();
    connect(sizeBtn, SIGNAL(clicked()), btnBoxSize, SLOT(slot_showOrHide()));
    btnBoxSize->setLayout(qVbox3);

    QVBoxLayout *qVbox = new QVBoxLayout;
    qVbox->setMargin(0);
    qVbox->setSpacing(0);
    qVbox->addWidget(rotateBtn);
    qVbox->addWidget(btnBoxRotate);
    qVbox->addWidget(cutBtn);
    qVbox->addWidget(btnBoxCut);
    qVbox->addWidget(sizeBtn);
    qVbox->addWidget(btnBoxSize);
    qVbox->addStretch();

    QWidget *t_widget = new QWidget;
    t_widget->setLayout(qVbox);

    setWidgetResizable(true);
    setWidget(t_widget);
}

BasicSetting::~BasicSetting()
{

}

//void BasicSetting::paintEvent(QPaintEvent *e)
//{
//    Q_UNUSED(e);

//    QPainter painter(this);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor("#414141"));
//    painter.drawRect(rect());
//}
