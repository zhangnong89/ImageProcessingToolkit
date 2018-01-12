#ifndef MENU_H
#define MENU_H
#include"all.h"

class QPushButton;
class QLabel;
class BasicSetting;
class AdvanceSetting;
class PuzzleSettingPage;

/*******************侧边菜单栏************************/
//下拉、收缩框
class ButtonBox : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonBox(QWidget *parent = 0);

public slots:
    void slot_showOrHide();
};



class SideMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideMenuBar(QWidget *parent = 0);
    ~SideMenuBar();
    BasicSetting *basicSettings;
    AdvanceSetting *advanceSettings;
    PuzzleSettingPage *puzzleSettings;
    void paintEvent(QPaintEvent *e);//background color

    QPushButton *t_primary;
    QPushButton *t_senior;
    QPushButton *t_puzzle;
signals:
public slots:
private:
  QTabWidget *tabWidget;

};


#endif // MENU_H
