#ifndef CUTDIALOG
#define CUTDIALOG
#include "all.h"

class CutDialog : public QFrame
{
    Q_OBJECT

public:
    explicit CutDialog(QWidget *parent = 0);
    ~CutDialog();
private:
    QRect getResizeGem(QRect oldgeo, QPoint mousePoint);

signals:
    void needMove(int dwidth, int dheight);
//    void sig_finishCut();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * );
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    QPoint m_startPoint;
    QPoint m_old_pos;
    bool m_isMoving;
    bool m_mouse_down;
    bool m_left;
    bool m_right;
    bool m_bottom;
    bool m_top;
    QLabel *label;
};























#endif // CUTDIALOG

