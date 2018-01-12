#include "titlebar.h"

TitleBar::TitleBar(const QPixmap &icon,
                   const QString &name,
                   TitleBarButtons buttons,
                   QWidget *parent) : QWidget(parent)
{
    setFixedHeight(28);

    //int t_buttonMask =

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->setSpacing(0);
    HLayout->setContentsMargins(5, 0 , 0, 0);

    m_appIcon = new QLabel;
    m_appIcon->setFixedSize(16, 16);
    m_appIcon->adjustSize();
    m_appIcon->setPixmap(icon);
    m_appIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    HLayout->addWidget(m_appIcon, 0, Qt::AlignVCenter);

    HLayout->addSpacing(4);

    m_appName=new QLabel;
    m_appName->setText(name);
    m_appName->adjustSize();
    m_appName->setObjectName("m_appName");
    m_appName->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    HLayout->addWidget(m_appName, 0, Qt::AlignVCenter);

    HLayout->addStretch(10);

    if((buttons & MinBtn) == MinBtn)
    {
        m_minBtn = new QPushButton;
        m_minBtn->setFixedSize(28, 28);
        m_minBtn->setToolTip("最小化");
        m_minBtn->setObjectName("m_minBtn");
        HLayout->addWidget(m_minBtn, 0, Qt::AlignTop);
        connect(m_minBtn, SIGNAL(clicked()), parent, SLOT(showMinimized()));
    }
    else
        m_minBtn = NULL;

    if((buttons & MaxBtn) == MaxBtn)
    {
        m_maxBtn = new QPushButton;
        m_maxBtn->setFixedSize(28, 28);
        m_maxBtn->setToolTip("最大化");
        m_maxBtn->setObjectName ("m_maxBtn");
        HLayout->addWidget(m_maxBtn, 0, Qt::AlignTop);
        connect(m_maxBtn, SIGNAL(clicked()), this, SLOT(slot_maximizedOrNo()));
    }
    else
        m_maxBtn = NULL;

    if((buttons & CloseBtn) == CloseBtn)
    {
        m_closeBtn = new QPushButton;
        m_closeBtn->setFixedSize(28, 28);
        m_closeBtn->setToolTip("关闭");
        m_closeBtn->setObjectName("m_closeBtn");
        HLayout->addWidget(m_closeBtn,0,Qt::AlignTop);
        connect(m_closeBtn, SIGNAL(clicked()), parent, SLOT(close()));
    }
    else
        m_closeBtn = NULL;

    setLayout(HLayout);

}

TitleBar::~TitleBar()
{

}

void TitleBar::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_dragPosition = e->globalPos() - parentWidget()->frameGeometry().topLeft();
        e->accept();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        parentWidget()->move(e->globalPos() - m_dragPosition);
        e->accept();
    }
}

void TitleBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#414141"));
    painter.drawRect(rect());
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    slot_maximizedOrNo();
}

void TitleBar::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    if(m_maxBtn != NULL)
    {
        if(parentWidget()->windowState() == Qt::WindowMaximized)
            m_maxBtn->setStyleSheet("QPushButton{image:url(:/images/recovery_normal.png);}");
        else //改变窗口大小时一直执行
            m_maxBtn->setStyleSheet("QPushButton{image:url(:/images/btn_max_normal.png);}");
    }
}

void TitleBar::slot_maximizedOrNo()
{
    if(parentWidget()->isMaximized())
        parentWidget()->showNormal();
    else
        parentWidget()->showMaximized();
}


