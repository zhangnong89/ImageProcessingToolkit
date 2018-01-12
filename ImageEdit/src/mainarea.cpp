#include "mainarea.h"

//#include"mainpage.h"

MainArea::MainArea(QWidget *parent) : QStackedWidget(parent)
{
     initPage= new InitPage;
     mainPage= new MainPage;

    addWidget(initPage);
    addWidget(mainPage);

    connect(initPage, SIGNAL(sig_openFile(QString)), this, SLOT(slot_changePage()));
    connect(initPage, SIGNAL(sig_openFile(QString)), mainPage,SLOT(slot_receivePictureFileName(QString)));
}

MainArea::~MainArea()
{

}

void MainArea::slot_changePage()
{
    setCurrentIndex(1);
}
