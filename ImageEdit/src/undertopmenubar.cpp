#include"undertopmenubar.h"
/*******************上部下面的菜单栏************************/
UnderTopMenuBar::UnderTopMenuBar(QWidget *parent)
{
    Q_UNUSED(parent);
    setAutoFillBackground(true);
    setPalette(QColor(Qt::gray));
    setFixedHeight(30);


    QPushButton *t_storeAction = new QPushButton("保存动作");
    QPushButton *t_undo = new QPushButton("撤销");
    QPushButton *t_redo = new QPushButton("重做");
    QPushButton *t_reset = new QPushButton("还原");
    QPushButton *t_compare = new QPushButton("对比");


    QHBoxLayout *t_1_hl = new QHBoxLayout;
    t_1_hl->setMargin(0);
    t_1_hl->setSpacing(0);

    t_1_hl->addWidget(t_storeAction);
    t_1_hl->addWidget(t_undo);
    t_1_hl->addWidget(t_redo);
    t_1_hl->addWidget(t_reset);
    t_1_hl->addStretch(1);
    t_1_hl->addWidget(t_compare);
//    t_1_hl->addWidget(t_fullScreen);
//    t_1_hl->addWidget(t_fitScreen);
//    t_1_hl->addWidget(t_originalSize);

    setLayout(t_1_hl);
}

UnderTopMenuBar::~UnderTopMenuBar()
{

}

