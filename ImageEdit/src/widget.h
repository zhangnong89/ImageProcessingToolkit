#ifndef WIDGET_H
#define WIDGET_H

#include"all.h"

class DragProxy;
class TitleBar;
class MainArea;
class TopMenuBar;
class BottomMenuBar;
class SideMenuBar;
class UnderTopMenuBar;
class QVBoxLayout;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *e);   //画边线
    void resizeEvent(QResizeEvent *e); //主要用于处理右键点击任务栏应用程序图标 中最大化 最小化功能

private:
    DragProxy *m_drag;                 //拖拉改变窗口大小类
    TitleBar *m_titleBar;
    MainArea *m_mainArea;              //包括了显示图片Widget 和 侧边栏
    BottomMenuBar *m_bottomMenuBar;    //最下面的菜单栏

    QRect m_availableRect;  //屏幕的大小除了任务栏
    QVBoxLayout *m_main_vl; //主布局
    QVBoxLayout *m_1_vl;    //主区域布局 边距为 1，0,1，0 左右个留出1个像素
};

#endif // WIDGET_H
