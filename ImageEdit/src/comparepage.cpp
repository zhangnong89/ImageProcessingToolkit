#include "comparepage.h"

ComparePage::ComparePage(QWidget* parent)
    : QWidget(parent)
{
    pictureView_1 = new PictureView(filePath);
    pictureView_2 = new PictureView(currentFilePath);

    QHBoxLayout* mainBox = new QHBoxLayout;
    mainBox->setMargin(0);
    mainBox->setSpacing(0);
    mainBox->addWidget(pictureView_1);
    mainBox->addWidget(pictureView_2);
    this->setLayout(mainBox);
}


void ComparePage::slot_receiveFirstImage(const QString& para_filePath)
{
    filePath = para_filePath;
    pictureView_1->setPixmapOnView(filePath);
}

void ComparePage::slot_receiveCurrentImage(const QString& para_currentFilePath)
{
    currentFilePath = para_currentFilePath;
    pictureView_2->setPixmapOnView(currentFilePath);
}

void ComparePage::mousePressEvent()
{
    emit sig_comparePressMouse();
}

ComparePage::~ComparePage()
{

}

