#ifndef PICTUREPUZZLE_H
#define PICTUREPUZZLE_H

#include"all.h"
class PictureView;
class CombineWidget_1;
class CombineWidget_2;
class CombineWidget_3;
class CombineWidget_4;
class PicturePuzzle : public QWidget
{

    Q_OBJECT

public:
    explicit PicturePuzzle(QWidget* parent = 0);
    ~PicturePuzzle();
    friend class MainPage;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void contextMenuEvent(QContextMenuEvent* event);
    QString openFileDialog(QWidget *parent, const QString defaultDir);

private:
    CombineWidget_1* combineWidget_1;
    CombineWidget_2* combineWidget_2;
    CombineWidget_3* combineWidget_3;
    CombineWidget_4* combineWidget_4;
    QStackedWidget* stackedWidget;
    QString firstFilePath;
    QString secondFilePath;
    PictureView* pictureViewPuzzle1_1;
    PictureView* pictureViewPuzzle1_2;
    PictureView* pictureViewPuzzle2_1;
    PictureView* pictureViewPuzzle2_2;
    PictureView* pictureViewPuzzle3_1;
    PictureView* pictureViewPuzzle3_2;
    PictureView* pictureViewPuzzle4_1;
    PictureView* pictureViewPuzzle4_2;
    QMenu* menu;
    QAction* addImageAction;
    QAction* saveImageAction;

signals:
    void sig_receiveSecondImg(const QString& para_secondFilePath);
    void sig_puzzle_saveSuccess();
public slots:
    void slot_receiveFirstImg(const QString& para_firstFilePath);    //current File Path
    void slot_receiveSecondImg(const QString& para_secondFilePath); //new File Path
    void slot_openFileDialog();
    void slot_puzzle_save();
};

#endif // PICTUREPUZZLE_H
