#include "adjustsizedialog.h"

AdjustSizeDialog::AdjustSizeDialog(QWidget *parent)
        : QDialog(parent)
{
        this->setFixedSize(250,150);

        setAttribute(Qt::WA_DeleteOnClose);  //关闭时释放
        setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog/*|Qt::WindowStaysOnTopHint*/);
//        setWindowFlags(Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint);
        setAutoFillBackground(true);
        setPalette(QPalette(Qt::darkGray));
        this->setWindowModality(Qt::ApplicationModal);


        wLabel=new QLabel("宽度");
        wLabel->setStyleSheet("color:white;");
        hLabel=new QLabel("高度");
        hLabel->setStyleSheet("color:white;");

        wInput=new QLineEdit;
        QRegExp rx("^[0-9]{1,4}$");

        QRegExpValidator*pReg=new QRegExpValidator(rx,this);
        wInput->setValidator(pReg);

        wLabel->setBuddy(wInput);

        hInput= new QLineEdit;
        hInput->setValidator(pReg);
        hLabel->setBuddy(hInput);

        wPixLabel=new QLabel("像素");
        wPixLabel->setStyleSheet("color:white;");
        hPixLabel=new QLabel("像素");
        hPixLabel->setStyleSheet("color:white;");
        lockRatio=new  QCheckBox("锁定宽高比");
        lockRatio->setStyleSheet("QCheckBox{color:white;background:transparent}");//set the background color and font color
        lockRatio->setChecked(true);


        QHBoxLayout*wPixLayout=new QHBoxLayout;
        wPixLayout->addWidget(wLabel);
        wPixLayout->addWidget(wInput);
        wPixLayout->addWidget(wPixLabel);

        QHBoxLayout*hpixLayout=new QHBoxLayout;
        hpixLayout->addWidget(hLabel);
        hpixLayout->addWidget(hInput);
        hpixLayout->addWidget(hPixLabel);

        QVBoxLayout *vPixLayout=new QVBoxLayout;
        vPixLayout->addLayout(wPixLayout);
        vPixLayout->addLayout(hpixLayout);

        QFrame* line1 = new QFrame;
        line1->setFixedWidth(20);

        line1->setFrameShape(QFrame::VLine);
//        line1->setFrameShadow(QFrame::Sunken);
        line1->setStyleSheet("color: darkGray");



        QHBoxLayout*basicHLayout=new QHBoxLayout;
        basicHLayout->addLayout(vPixLayout);
        basicHLayout->addWidget(line1/*, 0, Qt::AlignVCenter*/);
        basicHLayout->addWidget(lockRatio);


        QVBoxLayout *mainLayout=new QVBoxLayout;
        mainLayout->addLayout(basicHLayout);

        QFrame* line2 = new QFrame;
        line2->setFixedWidth(200);
        line2->setFrameShape(QFrame::HLine);
//        line2->setFrameShadow(QFrame::Sunken);
        line2->setStyleSheet("color: darkGray");
        mainLayout->addWidget(line2, 0, Qt::AlignHCenter);



        QHBoxLayout*bottomLayout=new QHBoxLayout;
        okBtn = new QPushButton("确定");
        QFont ft;
        ft.setBold(true);
        ft.setPointSize(10.5);
        ft.setFamily("Waree");


        okBtn->setFont(ft);
        okBtn->setFixedSize(78,28);
        okBtn->setStyleSheet("QPushButton{color: grey;"
                            "font:13px;"
                            "border: 1px;"     //去边框
                            "border-radius:3px;"
                            "border-style: solid;"
                            "border-color: grey;"
                            "background-color: rgb(255,255,255);}"
                            "QPushButton:hover{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgb(175, 212, 245));"
                            "border-color: rgb(135, 141, 155);}"
                            "QPushButton:pressed{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0),stop:1 rgba(155, 230, 245, 200));}"
                            );

        cancelBtn = new QPushButton("取消");
        cancelBtn->setFont(ft);
        cancelBtn->setFixedSize(78,28);
        cancelBtn->setStyleSheet("QPushButton{color: grey;"
                                "font:13px;"
                                "border: 1px;"     //去边框
                                "border-radius:3px;"
                                "border-style: solid;"
                                "border-color: grey;"
                                "background-color: rgb(255,255,255);}"

                                "QPushButton:hover{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgb(175, 212, 245));"
                                "border-color: rgb(135, 141, 155);}"
                                "QPushButton:pressed{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0),stop:1 rgba(155, 230, 245, 200));}"
                                );
        bottomLayout->setMargin(2);
        bottomLayout->setSpacing(8);
        bottomLayout->addStretch();
        bottomLayout->addWidget(okBtn);
        bottomLayout->addWidget(cancelBtn);

        mainLayout->addLayout(bottomLayout);
        this->setLayout(mainLayout);
        connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
        connect(wInput,SIGNAL(textEdited(QString)),this,SLOT(wInputChanged(QString)));
        connect(hInput,SIGNAL(textEdited(QString)),this,SLOT(hInputChanged(QString)));
}

AdjustSizeDialog::~AdjustSizeDialog()
{

}

void AdjustSizeDialog::hInputChanged(QString fileName)/*<3:4>*/
{
    if(this->lockRatio->isChecked())
    {
        int hNumber=0;
        bool ok;
        hNumber=fileName.toInt(&ok,10);
        hNumber = hNumber*4/3;

        QString numStr=QString::number(hNumber,10);
        this->wInput->setText(numStr);
    }
}

void AdjustSizeDialog::wInputChanged(QString fileName)/*<4:3>*/
{
    if(this->lockRatio->isChecked())
    {
        int hNumber=0;
        bool ok;
        hNumber=fileName.toInt(&ok,10);
        hNumber = hNumber*3/4;

        QString numStr=QString::number(hNumber,10);
        this->hInput->setText(numStr);
    }
}
