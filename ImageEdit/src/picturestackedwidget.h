#ifndef PICTURESTACKEDWIDGET_H
#define PICTURESTACKEDWIDGET_H
#include"all.h"

class PictureView;
class ComparePage;
class PicturePuzzle;

class PictureStackedWidget : public QStackedWidget
{

    Q_OBJECT

public:
    explicit PictureStackedWidget(PictureView*);
    ~PictureStackedWidget();
    friend class MainPage;

private:
    QString filePath;
    ComparePage* comparePage;
    PicturePuzzle* picturePuzzle;

public slots:
    void slot_changePage0();
    void slot_changePage1();
    void slot_changePage2();
};

#endif // PICTURESTACKEDWIDGET_H
