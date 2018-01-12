#include"puzzlesetting.h"
//拼图设置页
PuzzleSettingPage::PuzzleSettingPage(QWidget *parent)
{
    Q_UNUSED(parent);
    setAutoFillBackground(true);
    setPalette(QColor(12, 12, 12));

    templatePuzzle = new QPushButton("模板拼图");
    templatePuzzle->setStyleSheet("color:white; font:14px;");
//    freePuzzle = new QPushButton("自由拼图");
//    freePuzzle->setStyleSheet("color:white; font:14px;");
    optionPuzzle = new QPushButton("拼图操作");
    optionPuzzle->setStyleSheet("color:white; font:14px;");

//以后再添加此button
    puzzle_1 = new QPushButton("拼图模板1");
    puzzle_1->setToolTip("拼图模板1");
    puzzle_1->setStyleSheet("color:white; font:14px;");
    puzzle_1->setFixedHeight(48);
    puzzle_1->setFixedWidth(72);
//
    puzzle_2 = new QPushButton("拼图模板1");
    puzzle_2->setToolTip("拼图模板1");
//    puzzle_2->setStyleSheet("color:white; font:14px;");
    puzzle_2->setFixedHeight(48);
    puzzle_2->setFixedWidth(72);

    puzzle_3 = new QPushButton("拼图模板2");
    puzzle_3->setToolTip("拼图模板2");
//    puzzle_3->setStyleSheet("color:white; font:14px;");
    puzzle_3->setFixedHeight(48);
    puzzle_3->setFixedWidth(72);

    puzzle_4 = new QPushButton("拼图模板3");
    puzzle_4->setToolTip("拼图模板3");
//    puzzle_4->setStyleSheet("color:white; font:14px;");
    puzzle_4->setFixedHeight(48);
    puzzle_4->setFixedWidth(72);

   puzzleTemplateLayout = new QVBoxLayout;
   puzzleTemplateLayout->setSpacing(5);
   puzzleTemplateLayout->setContentsMargins(10, 10, 10, 10);
//   puzzleTemplateLayout->addWidget(puzzle_1, 0, Qt::AlignLeft);
   puzzleTemplateLayout->addWidget(puzzle_2, 0, Qt::AlignLeft);
   puzzleTemplateLayout->addWidget(puzzle_3, 0, Qt::AlignLeft);
   puzzleTemplateLayout->addWidget(puzzle_4, 0, Qt::AlignLeft);

   ButtonBox *btnBoxPuzzleTemplate = new ButtonBox;
   btnBoxPuzzleTemplate->hide();
   connect(templatePuzzle, SIGNAL(clicked()), btnBoxPuzzleTemplate, SLOT(slot_showOrHide()));
   btnBoxPuzzleTemplate->setLayout(puzzleTemplateLayout);


    puzzle_openNewFile = new QPushButton("加载图片");
    puzzle_openNewFile->setStyleSheet("color:white; font:14px;")   ;
    puzzle_save = new QPushButton("保存拼图");
    puzzle_save->setStyleSheet("color:white; font:14px;");

    puzzleOptionLayout = new QVBoxLayout;
    puzzleOptionLayout->setSpacing(5);
    puzzleOptionLayout->setContentsMargins(10, 10, 10, 10);
    puzzleOptionLayout->addWidget(puzzle_openNewFile, 0, Qt::AlignLeft);
    puzzleOptionLayout->addWidget(puzzle_save, 0, Qt::AlignLeft);

   ButtonBox *btnBoxOptionPuzzle = new ButtonBox;
   btnBoxOptionPuzzle->hide();
   connect(optionPuzzle, SIGNAL(clicked()), btnBoxOptionPuzzle, SLOT(slot_showOrHide()));
   btnBoxOptionPuzzle->setLayout(puzzleOptionLayout);

   QVBoxLayout *puzzleVbox = new QVBoxLayout;
   puzzleVbox->setMargin(0);
   puzzleVbox->setSpacing(0);
   puzzleVbox->addWidget(templatePuzzle);
   puzzleVbox->addWidget(btnBoxPuzzleTemplate);
//   puzzleVbox->addWidget(freePuzzle);
   puzzleVbox->addWidget(optionPuzzle);
   puzzleVbox->addWidget(btnBoxOptionPuzzle);
   puzzleVbox->addStretch();

   QWidget *puzzleMainWidget = new QWidget;
   puzzleMainWidget->setLayout(puzzleVbox);

   setWidgetResizable(true);
   setWidget(puzzleMainWidget);

    connect(this->templatePuzzle, SIGNAL(clicked()), this, SIGNAL(sig_templatePuzzlePress()));
    connect(this->puzzle_1, SIGNAL(clicked()), this, SIGNAL(sig_puzzle_1()));
    connect(this->puzzle_2, SIGNAL(clicked()), this, SIGNAL(sig_puzzle_2()));
    connect(this->puzzle_3, SIGNAL(clicked()), this, SIGNAL(sig_puzzle_3()));
    connect(this->puzzle_4, SIGNAL(clicked()), this, SIGNAL(sig_puzzle_4()));
//    connect(this->freePuzzle, SIGNAL(clicked()), this, SIGNAL(sig_freePuzzlePress()));
    connect(this->puzzle_save, SIGNAL(clicked()), this, SIGNAL(sig_puzzle_save()));
    connect(this->puzzle_openNewFile, SIGNAL(clicked()), this, SIGNAL(sig_puzzle_openNewFile()));
}

void PuzzleSettingPage::slot_puzzle_saveSuccess()
{
    puzzle_save->setText("保存成功");
}

PuzzleSettingPage::~PuzzleSettingPage()
{

}
