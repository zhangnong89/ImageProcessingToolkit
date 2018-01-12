#include "picturepuzzlewidget.h"

CombineWidget_1::CombineWidget_1(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2)
    : QWidget()
{
    QHBoxLayout* puzzleBox_1 = new QHBoxLayout;
    puzzleBox_1->setMargin(0);
    puzzleBox_1->setSpacing(0);
    puzzleBox_1->addWidget(pictureViewPuzzle_1, Qt::AlignCenter);
    puzzleBox_1->addWidget(pictureViewPuzzle_2, Qt::AlignCenter);
    this->setLayout(puzzleBox_1);
}

CombineWidget_1::~CombineWidget_1()
{

}

CombineWidget_2::CombineWidget_2(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2)
    : QWidget()
{
    QVBoxLayout* puzzleBox_2 = new QVBoxLayout;
    puzzleBox_2->setMargin(0);
    puzzleBox_2->setSpacing(0);
    puzzleBox_2->addWidget(pictureViewPuzzle_1);
    puzzleBox_2->addWidget(pictureViewPuzzle_2);
    this->setLayout(puzzleBox_2);
}

CombineWidget_2::~CombineWidget_2()
{

}

CombineWidget_3::CombineWidget_3(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2)
    : QWidget()
{
    QHBoxLayout* puzzleBox_3 = new QHBoxLayout;
    puzzleBox_3->setMargin(0);
    puzzleBox_3->setSpacing(0);
    puzzleBox_3->addWidget(pictureViewPuzzle_1);
    puzzleBox_3->addWidget(pictureViewPuzzle_2);
    this->setLayout(puzzleBox_3);
}

CombineWidget_3::~CombineWidget_3()
{

}

CombineWidget_4::CombineWidget_4(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2)
    : QWidget()
{   
    QHBoxLayout* puzzleBox_4 = new QHBoxLayout;
    puzzleBox_4->setMargin(0);
    puzzleBox_4->setSpacing(0);
    puzzleBox_4->addWidget(pictureViewPuzzle_1, Qt::AlignCenter);
    puzzleBox_4->addWidget(pictureViewPuzzle_2, Qt::AlignCenter);
    this->setLayout(puzzleBox_4);
}

CombineWidget_4::~CombineWidget_4()
{

}
