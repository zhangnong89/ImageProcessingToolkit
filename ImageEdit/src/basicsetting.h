#ifndef BASICSETTING
#define BASICSETTING
#include"all.h"
//基础设置页
class BasicSetting: public QScrollArea
{
    Q_OBJECT

public:
    explicit BasicSetting(QWidget *parent = 0);
    ~BasicSetting();
//    void paintEvent(QPaintEvent *e);

//main label


    QPushButton *rotateBtn ;
    QPushButton *cutBtn;
    QPushButton *sizeBtn;

//rotate setting
    QPushButton *rotateLeft ;
    QPushButton *rotateRight ;
    QPushButton *rotateLR ;
    QPushButton *rotateUD ;


//adjust size
    QPushButton *freeAdjustSize ;
//    QPushButton *keepRatioAdjustSize ;
    QPushButton *w800;
    QPushButton *w1200;
    QPushButton *w1600;

protected:
//cut
    QPushButton *freeCutting;
    QPushButton *pictureCut;
    QPushButton *normalWallCut;
    QPushButton *wideWallCut;
    QPushButton *inch1Cut;
    QPushButton *inch2Cut;


signals:
      void sig_rotateLeft();
      void sig_rotateRight();
      void sig_rotateFront();
      void sig_rotateBack();

      void sig_freeCutting();

      void sig_pictureCut();
      void sig_normalWallCut();
      void sig_wideWallCut();
      void sig_inch1Cut();
      void sig_inch2Cut();
      void sig_freeAdjustSize();

      void sig_w800();
      void sig_w1200();
      void sig_w1600();
public slots:
};

#endif // BASICSETTING

