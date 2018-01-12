#include "menu.h"

/*******************侧边菜单栏************************/

ButtonBox::ButtonBox(QWidget *parent) : QWidget(parent)
{

}

void ButtonBox::slot_showOrHide()
{
    if(isHidden())
        show();
    else
        hide();
}



SideMenuBar::SideMenuBar(QWidget *parent) : QWidget(parent)
{
 #if 1
    Q_UNUSED(parent);
    setAutoFillBackground(true);
    setPalette(QColor(Qt::white));
    setFixedWidth(SIDEMENUBAR_W);

    QSignalMapper *t_mapper = new QSignalMapper;

    t_primary = new QPushButton("");
    t_primary->setStyleSheet("border-image:url(:/basicImages/menu_basic.jpg);");
    t_primary->setFlat(true);
    t_primary->setFixedHeight(74);
    t_primary->setFixedWidth(46);

    t_mapper->setMapping(t_primary, 0);
    connect(t_primary, SIGNAL(clicked()), t_mapper, SLOT(map()));

    t_senior = new QPushButton("");
    t_senior->setFlat(true);
    t_senior->setStyleSheet("border-image:url(:/basicImages/menu_advanced.jpg);");
    t_senior->setFixedHeight(76);
    t_senior->setFixedWidth(46);
    t_mapper->setMapping(t_senior, 1);
    connect(t_senior, SIGNAL(clicked()), t_mapper, SLOT(map()));

    t_puzzle = new QPushButton("");
    t_puzzle->setStyleSheet("border-image:url(:/basicImages/menu_puzzle.jpg);");
    t_puzzle->setFlat(true);
    t_puzzle->setFixedHeight(74);
    t_puzzle->setFixedWidth(46);
    t_mapper->setMapping(t_puzzle, 2);
    connect(t_puzzle, SIGNAL(clicked()), t_mapper, SLOT(map()));

    QVBoxLayout *t_1_hl = new QVBoxLayout;
    t_1_hl->setMargin(0);
    t_1_hl->setSpacing(0);

    t_1_hl->addWidget(t_primary);
    t_1_hl->addWidget(t_senior);
    t_1_hl->addWidget(t_puzzle);

    t_1_hl->addStretch(1);


//    QPainter painter(this);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor("#414141"));
//    painter.drawRect(rect());



    QStackedWidget *stackWidget = new QStackedWidget;
    stackWidget->setAutoFillBackground(true);
//    stackWidget->setFixedWidth(100);


    stackWidget->setStyleSheet("background-color: rgb(65,65,65)");

    basicSettings = new BasicSetting;
    advanceSettings = new AdvanceSetting;
    puzzleSettings = new PuzzleSettingPage;

    stackWidget->addWidget(basicSettings);
    stackWidget->addWidget(advanceSettings);
    stackWidget->addWidget(puzzleSettings);

    QHBoxLayout *t_1_vl = new QHBoxLayout;
    t_1_vl->setMargin(0);
    t_1_vl->setSpacing(0);

    t_1_vl->addLayout(t_1_hl);
    t_1_vl->addWidget(stackWidget);

    setLayout(t_1_vl);

   connect(t_mapper, SIGNAL(mapped(int)), stackWidget, SLOT(setCurrentIndex(int)));
#endif
}

SideMenuBar::~SideMenuBar()
{

}

void SideMenuBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#1d1d1d"));
    painter.drawRect(rect());
}
