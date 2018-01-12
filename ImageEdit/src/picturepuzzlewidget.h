#ifndef PICTUREPUZZLEWIDGET_H
#define PICTUREPUZZLEWIDGET_H
#include"all.h"
class PictureView;

class  CombineWidget_1: public QWidget
{
    Q_OBJECT
public:
    explicit CombineWidget_1(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2);
    ~CombineWidget_1();
};

class  CombineWidget_2: public QWidget
{
    Q_OBJECT
public:
    explicit CombineWidget_2(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2);
    ~CombineWidget_2();
};

class  CombineWidget_3: public QWidget
{
    Q_OBJECT
public:
    explicit CombineWidget_3(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2);
    ~CombineWidget_3();

};

class  CombineWidget_4: public QWidget
{
    Q_OBJECT
public:
    explicit CombineWidget_4(PictureView* pictureViewPuzzle_1, PictureView* pictureViewPuzzle_2);
    ~CombineWidget_4();
};

#endif // PICTUREPUZZLEWIDGET_H
