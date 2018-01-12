#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setMinimumHeight(MIN_H);
    setMinimumWidth(MIN_W);
    setFocusPolicy(Qt::StrongFocus);

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move(((desktop->width() - this->width())/2)/2, (desktop->height() - this->height())/3);
//    resize(1425,870);

    m_drag = new DragProxy(this);
    m_drag->SetBorderWidth(MARGIN , MARGIN, MARGIN, MARGIN);

    //不包含任务栏 screenGeometry()是获得整个屏幕大小
    m_availableRect = QApplication::desktop()->availableGeometry();

    m_titleBar = new TitleBar(QPixmap(":/images/logo.svg"),
                              QString("图片编辑"),
                              TitleBar::MinBtn | TitleBar::MaxBtn | TitleBar::CloseBtn,
                              this);

    m_mainArea = new MainArea;
    m_bottomMenuBar = new BottomMenuBar;

//set a connect to enable the picInfo button
//    connect(initPage, SIGNAL(sig_openFile(QString)), this, SLOT(slot_changePage()));
    connect(m_mainArea->initPage,SIGNAL(sig_openFile(QString)) ,m_bottomMenuBar,SLOT(enablePicInfoCallbackFunc(QString)));
    connect(m_mainArea->mainPage,SIGNAL(sig_openFile(QString)) ,m_bottomMenuBar,SLOT(enablePicInfoCallbackFunc(QString)));
    connect(m_mainArea->mainPage->topMenuBar,SIGNAL(sig_openFile(QString)),m_bottomMenuBar,SLOT(enablePicInfoCallbackFunc(QString)));

    connect(m_mainArea->initPage,SIGNAL(sig_openFile(QString)) ,m_mainArea->mainPage->topMenuBar,SLOT(slot_initialFile(QString)));


//    connect(m_bottomMenuBar->picNarrow,SIGNAL(clicked()),m_mainArea->mainPage,SLOT(slot_narrowCurrentImage()));
//    connect(m_bottomMenuBar->picEnlarge,SIGNAL(clicked()),m_mainArea->mainPage,SLOT(slot_enlargeCurrentImage()));
    connect(m_bottomMenuBar, SIGNAL(sig_picAdjustSize(bool)), m_mainArea->mainPage->pictureView, SLOT(slot_zoom(bool)));

    m_1_vl = new QVBoxLayout;
    m_1_vl->setContentsMargins(1,0,1,0);
    m_1_vl->setSpacing(0);

    m_1_vl->addWidget(m_mainArea);
    m_1_vl->addWidget(m_bottomMenuBar);

    m_bottomMenuBar->hide();

    QWidget *t_widget = new QWidget;
    t_widget->setLayout(m_1_vl);

    m_main_vl = new QVBoxLayout;
    m_main_vl->addWidget(m_titleBar);
    m_main_vl->addWidget(t_widget);
    m_main_vl->setMargin(MARGIN);

    setLayout(m_main_vl);

    resize(WIN_W, WIN_H);
    m_main_vl->setSpacing(0);
}

Widget::~Widget()
{

}

void Widget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    if(m_availableRect == rect())
    {
        m_main_vl->setMargin(0);
        m_1_vl->setMargin(0);
    }
    else
    {
        if(m_main_vl->margin() != MARGIN && m_1_vl->contentsMargins() != QMargins(1,0,1,0))
        {
            m_main_vl->setMargin(MARGIN);
            m_1_vl->setContentsMargins(1,0,1,0);
        }
    }
}

void Widget::paintEvent(QPaintEvent *e)
{
     Q_UNUSED(e);
    if(!isFullScreen())   //全屏时不需要画框
    {
        QPainter painter(this);
        painter.setPen(QColor(125, 162, 195));
        painter.drawRect(5, 33, width()-11, height()-38);
    }
}
