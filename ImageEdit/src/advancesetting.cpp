#include"advancesetting.h"
//高级设置页
AdvanceSetting::AdvanceSetting(QWidget *parent)
{
    Q_UNUSED(parent);
    setAutoFillBackground(true);
    setPalette(QColor(23, 213, 23));

    QPushButton *filterBtn = new QPushButton("滤镜处理");
    filterBtn->setStyleSheet("color:white; font:14px;");
    QPushButton *mosaicBtn = new QPushButton("马赛克");
    mosaicBtn->setStyleSheet("color:white; font:14px;");
    QPushButton *formatConvertBtn = new QPushButton("格式转换");
    formatConvertBtn->setStyleSheet("color:white; font:14px;"); 


/***********************************************************/
/*****************制作滑动条*********************/
//亮度
    QLabel *BrightLabel = new QLabel("");
    BrightLabel->setPixmap(QPixmap(":/AdvancedImages/bright_icon.png"));
    BrightLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    BrightSlider = new QSlider(Qt::Vertical);
    BrightSlider->setRange(-255, 255);
    //BrightSlider->setValue(0);

    brightPerLbl = new QLabel("0");
//    brightPerLbl->setStyleSheet("color:white; font:14px;");
    imageNumber(brightPerLbl);

    QVBoxLayout *brightVbox=new QVBoxLayout;
    brightVbox->setMargin(0);
    brightVbox->setSpacing(0);
    brightVbox->addWidget(BrightLabel);
    brightVbox->addWidget(BrightSlider);
    brightVbox->addWidget(brightPerLbl);

    //wheelEvent(brightVbox,BrightSlider);

 //对比度
    QLabel *ContrastLabel = new QLabel("");
    ContrastLabel->setPixmap(QPixmap(":/AdvancedImages/contrast_icon.png"));
    ContrastLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ContrastSlider = new QSlider(Qt::Vertical);
    ContrastSlider->setRange(-255, 255);
    ContrastSlider->setValue(0);

    contrastPerLbl = new QLabel("0");
    contrastPerLbl->setStyleSheet("color:white; font:14px;");
    imageNumber(contrastPerLbl);

    QVBoxLayout *contrastVbox = new QVBoxLayout;
    contrastVbox->setMargin(0);
    contrastVbox->setSpacing(0);
    contrastVbox->addWidget(ContrastLabel);
    contrastVbox->addWidget(ContrastSlider);
    contrastVbox->addWidget(contrastPerLbl);

//色彩饱和度调节
    QLabel *colorSaturationLabel = new QLabel("");
    colorSaturationLabel->setPixmap(QPixmap(":/AdvancedImages/colour_saturation_icon.png"));
    colorSaturationLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    colorSaturationSlider = new QSlider(Qt::Vertical);
    colorSaturationSlider->setRange(-100, 100);
    colorSaturationSlider->setValue(0);

    colorSaturationPerLbl = new QLabel("0");
    colorSaturationPerLbl->setStyleSheet("color:white; font:14px;");
    imageNumber(colorSaturationPerLbl);

    QVBoxLayout *colorSaturationVbox = new QVBoxLayout;
    colorSaturationVbox->setMargin(0);
    colorSaturationVbox->setSpacing(0);
    colorSaturationVbox->addWidget(colorSaturationLabel);
    colorSaturationVbox->addWidget(colorSaturationSlider);
    colorSaturationVbox->addWidget(colorSaturationPerLbl);

//清晰度调节
    QLabel *resolutionLabel = new QLabel("");
    resolutionLabel->setPixmap(QPixmap(":/AdvancedImages/resolution_icon.png"));
    resolutionLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    resolutionSlider = new QSlider(Qt::Vertical);
    resolutionSlider->setRange(-250,250);
    resolutionSlider->setValue(0);

    resolutionPerLbl = new QLabel("0");
    resolutionPerLbl->setStyleSheet("color:white; font:14px;");
    imageNumber( resolutionPerLbl);

    QVBoxLayout *resolutionVbox = new QVBoxLayout;
    resolutionVbox->setMargin(0);
    resolutionVbox->setSpacing(0);
    resolutionVbox->addWidget(resolutionLabel);
    resolutionVbox->addWidget(resolutionSlider);
    resolutionVbox->addWidget(resolutionPerLbl);

    QHBoxLayout *hbox1= new QHBoxLayout;
    hbox1->addLayout(brightVbox);
    hbox1->addLayout(contrastVbox);
    QHBoxLayout *hbox2= new QHBoxLayout;
    hbox2->addLayout(colorSaturationVbox);
    hbox2->addLayout(resolutionVbox);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    ButtonBox *filterBtnBox = new ButtonBox;
    filterBtnBox->hide();
    connect(filterBtn, SIGNAL(clicked()), filterBtnBox, SLOT(slot_showOrHide()));
    filterBtnBox->setLayout(vbox);

    //信号和槽 当滑动条的值发生改变时，即产生一个valueChanged(int)信号 设置QLineEdit控件的显示文本
    connect(BrightSlider, SIGNAL(valueChanged(int)), this, SLOT(slot_BrightSetValue(int)));
    connect(ContrastSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_ContrastSetValue(int)));
    connect(colorSaturationSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_colorSaturationSetValue(int)));
    connect(resolutionSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_resolutionSetValue(int)));

    connect(BrightSlider, SIGNAL(sliderReleased()), this, SIGNAL(sig_sliderIsReleased()));
    connect(ContrastSlider, SIGNAL(sliderReleased()), this, SIGNAL(sig_sliderIsReleased()));
    connect(colorSaturationSlider, SIGNAL(sliderReleased()), this, SIGNAL(sig_sliderIsReleased()));
    connect(resolutionSlider, SIGNAL(sliderReleased()), this, SIGNAL(sig_sliderIsReleased()));
/******************************************************SLOT**/
//马赛克
   mosaicBrush = new QPushButton("");
   mosaicBrush->setToolTip("画笔");
   mosaicBrush->setFixedWidth(72);
   mosaicBrush->setFixedHeight(48);
   mosaicBrush->setStyleSheet("QPushButton{border-image:url(:/AdvancedImages/mosaic_brush_normal.png);}"
                              "QPushButton:hover{border-image:url(:/AdvancedImages/mosaic_brush_focus.png);}"
                              "QPushButton:pressed{border-image:url(:/AdvancedImages/mosaic_brush_clicked.png);}");
   mosaicEraser  = new QPushButton("");
   mosaicEraser->setToolTip("橡皮擦");
   mosaicEraser->setFixedWidth(72);
   mosaicEraser->setFixedHeight(48);
   mosaicEraser->setStyleSheet("QPushButton{border-image:url(:/AdvancedImages/mosaic_eraser_normal.png);}"
                               "QPushButton:hover{border-image:url(:/AdvancedImages/mosaic_eraser_focus.png);}"
                               "QPushButton:pressed{border-image:url(:/AdvancedImages/mosaic_eraser_clicked.png);}");

    QVBoxLayout *mosaicBox = new QVBoxLayout;
    mosaicBox->setSpacing(5);
    mosaicBox->setContentsMargins(10, 10, 10, 10);
    mosaicBox->addWidget(mosaicBrush, 0, Qt::AlignLeft);
    mosaicBox->addWidget(mosaicEraser, 0, Qt::AlignLeft);

    ButtonBox *mosaicBtnBox = new ButtonBox;
    mosaicBtnBox->hide();
    connect(mosaicBtn, SIGNAL(clicked()), mosaicBtnBox, SLOT(slot_showOrHide()));
    mosaicBtnBox->setLayout(mosaicBox);

//Mosaic click slot
        connect(mosaicBrush,SIGNAL(clicked()),this,SIGNAL(sig_mosaicBrush()));
        connect(mosaicEraser,SIGNAL(clicked()),this,SIGNAL(sig_mosaicEraser()));
/*******************************************************/
//格式转化
        dateTime  = new QDateTime;
        current_date = dateTime->currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
        convertEdit = new QLineEdit(current_date);
        convertEdit->setStyleSheet("color:white; font:9px;");
        convertCombo = new QComboBox;
        QStringList stringList;
        stringList << "png" << "jpeg" << "bmp";
        convertCombo->addItems(stringList);
        convertCombo->setStyleSheet("color:white; font:14px;");
        convertBtn = new QPushButton("开始转换");
        convertBtn->setStyleSheet("color:white; font:14px;");
        convertBtn->setFixedSize(60, 25);
        QVBoxLayout* convertVbox=new QVBoxLayout;
//        QHBoxLayout* convertHbox=new QHBoxLayout;
        convertVbox->setSpacing(12);
        convertVbox->addWidget(convertEdit, 0, Qt::AlignCenter);
        convertVbox->addWidget(convertCombo, 0, Qt::AlignRight);
//        convertVbox->addLayout(convertHbox);
        convertVbox->addWidget(convertBtn, 0, Qt::AlignHCenter);
        ButtonBox *convertBtnBox = new ButtonBox;
        convertBtnBox->hide();
        connect(formatConvertBtn, SIGNAL(clicked()), convertBtnBox, SLOT(slot_showOrHide()));
        convertBtnBox->setLayout(convertVbox);
        connect(convertBtn, SIGNAL(clicked()), this, SLOT(slot_convertBegin()));
/*******************************************************/
    QVBoxLayout *t_1_vl = new QVBoxLayout;
    t_1_vl->setMargin(0);
    t_1_vl->setSpacing(0);
    t_1_vl->addWidget(filterBtn);
    t_1_vl->addWidget(filterBtnBox);
    t_1_vl->addWidget(mosaicBtn);
    t_1_vl->addWidget(mosaicBtnBox);
    t_1_vl->addWidget(formatConvertBtn);
    t_1_vl->addWidget(convertBtnBox);
    t_1_vl->addStretch();

    QWidget *t_widget = new QWidget;
    t_widget->setLayout(t_1_vl);

    setWidgetResizable(true);
    setWidget(t_widget);
}

//void AdvanceSetting::paintEvent(QPaintEvent *e)
//{
//    Q_UNUSED(e);

//    QPainter painter(this);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor("#414141"));
//    painter.drawRect(rect());
//}

///滤镜SLOT
 void AdvanceSetting::slot_BrightSetValue(int)
{
    int pos_BrightSlider = BrightSlider->value();
    QString str_BrightSlider = QString("%1").arg(pos_BrightSlider);
    brightPerLbl ->setText(str_BrightSlider);
    imageNumber(brightPerLbl);
    sig_BrightSlider(pos_BrightSlider);
}
void AdvanceSetting::slot_ContrastSetValue(int)
{
    int pos_ContrastSlider = ContrastSlider->value();
    QString str_ContrastSlider = QString("%1").arg(pos_ContrastSlider);
    contrastPerLbl->setText(str_ContrastSlider);
    imageNumber(contrastPerLbl);
    sig_ContrastSlider(pos_ContrastSlider);

}
void AdvanceSetting::slot_colorSaturationSetValue(int)
{
    int pos_colorSaturationSlider = colorSaturationSlider->value();
    QString str_colorSaturationSlider = QString("%1").arg(pos_colorSaturationSlider);
    colorSaturationPerLbl->setText(str_colorSaturationSlider);
    imageNumber(colorSaturationPerLbl);
    sig_colorSaturationSlider(pos_colorSaturationSlider);

 }
void AdvanceSetting::slot_resolutionSetValue(int)
{
    int pos_resolutionSlider = resolutionSlider->value();
    QString str_resolutionSlider= QString("%1").arg(pos_resolutionSlider);
    resolutionPerLbl->setText(str_resolutionSlider);
    imageNumber(resolutionPerLbl);
    sig_resolutionSlider(pos_resolutionSlider);

}

void AdvanceSetting::imageNumber(QLabel *label)
{
    QImage image=QPixmap(":/AdvancedImages/filter_general_percentage.png").toImage();
//为这个QImage构造一个QPainter
    QPainter painter(&image);
//设置画刷的组合模式CompositionMode_SourceOut这个模式为目标图像在上。
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
//改变画笔和字体
    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    QFont font = painter.font();
    font.setBold(false);//加粗
    font.setPixelSize(14);//改变字体大小
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(image.rect(),Qt::AlignCenter,label->text());
    label->setPixmap(QPixmap::fromImage(image));
}

//初始化Slider
void AdvanceSetting::slot_initSlider()
{
    BrightSlider->setValue(0);
    brightPerLbl->setText("0");
    imageNumber(brightPerLbl);
    ContrastSlider->setValue(0);
    contrastPerLbl->setText("0");
    imageNumber(contrastPerLbl);
    colorSaturationSlider->setValue(0);
    colorSaturationPerLbl->setText("0");
    imageNumber(colorSaturationPerLbl);
    resolutionSlider->setValue(0);
    resolutionPerLbl->setText("0");
    imageNumber(resolutionPerLbl);
}

//格式转化, 更新时间
void AdvanceSetting::slot_convertBegin()
{
    bool lineEditFlag;
    QString lineEditText;
    QString comboText;
//判断用户是否有输入
    lineEditFlag = convertEdit->isModified();
    lineEditText = convertEdit->text();
    current_date = dateTime->currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    if(!lineEditFlag||lineEditText==0)
    {
        convertEdit->setText(current_date);
        lineEditText = current_date;
    }
    else
    {
        lineEditText = this->convertEdit->text();

    }
    comboText = this->convertCombo->currentText();
    sig_convertBegin(lineEditText, comboText);
    sig_formatConvert();
//点过之后，按钮不可按
    this->convertBtn->setEnabled(false);
}

void AdvanceSetting::slot_convertSuccess()
{
    this->convertBtn->setText("转换成功");
    QElapsedTimer* timer = new QElapsedTimer;
    timer->start();
//等待一秒钟
    while(timer->elapsed()<1000)
        QCoreApplication::processEvents();
    this->convertBtn->setText("开始转换");
    this->convertBtn->setEnabled(true);
}

AdvanceSetting::~AdvanceSetting()
{

}

