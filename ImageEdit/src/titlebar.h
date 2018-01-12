#ifndef TITLEBAR_H
#define TITLEBAR_H
#include"all.h"

class QPushButton;
class QLabel;


class TitleBar : public QWidget
{
    Q_OBJECT
public:

    enum TitleBarButton
    {
        Nobtn = 0x00,
        MinBtn = 0x01,
        MaxBtn = 0x02,
        CloseBtn = 0x04,
    };

    typedef QFlags<TitleBarButton> TitleBarButtons;

    explicit TitleBar(const QPixmap &icon,
                      const QString &name,
                      TitleBarButtons buttons = Nobtn,
                      QWidget *parent = 0);
    ~TitleBar();

    void mousePressEvent(QMouseEvent *e);         //记录点击的点
    void mouseMoveEvent(QMouseEvent *e);          //移动窗口
    void paintEvent(QPaintEvent *e);              //绘制背景
    void mouseDoubleClickEvent(QMouseEvent *e);   //双击全屏
    void resizeEvent(QResizeEvent *e);            //设置最大化按钮图标

private:
    QPushButton *m_minBtn;
    QPushButton *m_maxBtn;
    QPushButton *m_closeBtn;
    QPoint m_dragPosition;    //记录鼠标按下时 坐标
    QLabel *m_appName;        //标题栏左上角 名称
    QLabel *m_appIcon;        //标题栏坐上角 logo

public slots:
    void slot_maximizedOrNo();   //点击最大化按钮 执行此函数 控制窗口的 最大化和回复
};

//重载 | 使能用 “TitleBar::MinBtn | TitleBar::MaxBtn | TitleBar::CloseBtn”形式的参数
Q_DECLARE_OPERATORS_FOR_FLAGS(TitleBar::TitleBarButtons)


#endif // TITLEBAR_H
