#include "picturestackedwidget.h"

PictureStackedWidget::PictureStackedWidget(PictureView* pictureView)
    : QStackedWidget()
{
    comparePage = new ComparePage;
    picturePuzzle = new PicturePuzzle;
    addWidget(pictureView);
    addWidget(comparePage);
    addWidget(picturePuzzle);
}

void PictureStackedWidget::slot_changePage0()
{
    this->setCurrentIndex(0);
}

void PictureStackedWidget::slot_changePage1()
{
    this->setCurrentIndex(1);
}

void PictureStackedWidget::slot_changePage2()
{
    this->setCurrentIndex(2);
}

PictureStackedWidget::~PictureStackedWidget()
{

}

