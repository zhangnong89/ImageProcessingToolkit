#ifndef MAINAREA_H
#define MAINAREA_H
#include"all.h"

//#include "initpage.h"
//#include "mainpage.h"

class MainPage;
class InitPage;
class MainArea : public QStackedWidget
{
    Q_OBJECT

public:
    MainArea(QWidget *parent=0);
    InitPage *initPage;
    MainPage *mainPage;
    ~MainArea();

public slots:
    void slot_changePage();
};

#endif // MAINAREA_H
