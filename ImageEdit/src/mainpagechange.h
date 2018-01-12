#ifndef MAINPAGECHANGE_H
#define MAINPAGECHANGE_H
#include"all.h"

class PictureView;
class PicturePuzzle;
class MainPage;
class SideMenuBar;
class MainPageChange : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MainPageChange(QWidget* parent = 0);
    ~MainPageChange();

    QString currentFilePath;
    PictureView* pictureView;
    PicturePuzzle* picturePuzzle;
    MainPage* mainPage;
    SideMenuBar* sideMenuBar;

public slots:
//change the page of mainpage, about puzzle and compare
    void slot_changePuzzlePage();

};

#endif // MAINPAGECHANGE_H
