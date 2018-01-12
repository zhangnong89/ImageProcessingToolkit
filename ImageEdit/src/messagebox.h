#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include "all.h"


enum Checked
{
    Ok,
    Cancel,
    Cover,
};

class tilebarForMessageBox : public QWidget
{
    Q_OBJECT

public:

    QPoint dragPosition;
    QPushButton *m_close;
    QLabel *m_title;

    tilebarForMessageBox(QWidget *parent = 0) : QWidget(parent)
    {
        setFixedHeight(28);
        setAutoFillBackground(true);
        setStyleSheet("background: rgb(175, 212, 245);"
                       "color: rgb(255, 255, 255);"
                       "font:13px;");

        m_close = new QPushButton;
        m_close->setFixedSize(28, 28);
        m_close->setStyleSheet("QPushButton{border-image:url(:/prefix1/1-images/btn_close_nomal.png);}"
                                 "QPushButton:hover{border-image:url(:/prefix1/1-images/btn_close_hover.png);}"
                                 "QPushButton:pressed{border-image:url(:/prefix1/1-images/btn_close_pressed.png);}");

        m_title = new QLabel("提示");
        m_title->setContentsMargins(5, 0, 0, 0);
        m_title->setAlignment(Qt::AlignCenter);

        QHBoxLayout *t_hl = new QHBoxLayout;
        t_hl->setMargin(0);
        t_hl->addWidget(m_title);
        t_hl->addStretch(0);
        t_hl->addWidget(m_close);

        setLayout(t_hl);
    }

    ~tilebarForMessageBox()
    {

    }

    void mousePressEvent(QMouseEvent *e)
    {
        if (e->button() == Qt::LeftButton)
        {
              dragPosition = e->globalPos() - this->parentWidget()->frameGeometry().topLeft();
              e->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *e)
    {
        if (e->buttons() & Qt::LeftButton)
        {
                this->parentWidget()->move(e->globalPos() - dragPosition);

                e->accept();
        }
    }

    //setstylesheet() 不管用
    void paintEvent(QPaintEvent *e)
    {
        QWidget::paintEvent(e);
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
};


class mainArea : public QScrollArea
{
    Q_OBJECT

public:
    mainArea(QWidget *parent = 0) : QScrollArea(parent)
    {
        setFixedWidth(260);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setWidgetResizable(true);
        setStyleSheet("background:transparent; border:0px");

        m_info = new QLabel(this);

        m_info->setStyleSheet("color: grey;"
                               "font:13px;");
        m_info->setWordWrap(true);
        m_info->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
        setWidget(m_info);
    }

    ~mainArea()
    {

    }

    void setInfo(const QString text)
    {

        QString t_text = text;
        if(t_text.length() > 26)
            for(int i = 25; i < t_text.length(); i+=24)
            {
                t_text.insert(i, QString(" "));
            }
        m_info->setText(t_text);
    }

private:
    QLabel *m_info;
};

class MessageBox : public QDialog
{
    Q_OBJECT

public:

    QPushButton *m_2_btn;

    MessageBox(const QString &nameForBtn1, const QString &nameForBtn2,
                 const QString &nameForBtn3, const bool &isShowBtn3,
                 const QPixmap &icon, const QString &text,
                 QWidget *parent = 0, Qt::WindowFlags f = 0)
        : QDialog(parent, f), m_checked(Cancel)
    {
        resize(320, 158);
        setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        setAutoFillBackground(true);
        setStyleSheet("background: white; color:grey;");

        QPushButton *t_1_btn = new QPushButton(nameForBtn1, this);
        t_1_btn->setFixedSize(68, 26);
        t_1_btn->setStyleSheet("QPushButton{font:13px;"
                            "border: 1px;"
                            "border-radius:3px;"
                            "border-style: solid;"
                            "border-color: grey;"
                            "background-color: rgb(255,255,255);}"
                            "QPushButton:hover{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgb(175, 212, 245));"
                            "border-color: rgb(135, 141, 155);}");

        m_2_btn = new QPushButton(nameForBtn2, this);
        m_2_btn->setFixedSize(68, 26);
        m_2_btn->setStyleSheet("QPushButton{font:13px;"
                            "border: 1px;"
                            "border-radius:3px;"
                            "border-style: solid;"
                            "border-color: grey;"
                            "background-color: rgb(255,255,255);}"
                            "QPushButton:hover{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgb(175, 212, 245));"
                            "border-color: rgb(135, 141, 155);}");

        QPushButton *t_3_btn = new QPushButton(nameForBtn3, this);
        t_3_btn->setFixedSize(78, 26);;
        t_3_btn->setStyleSheet("QPushButton{font:13px;"
                                         "border: 1px;"
                                         "border-radius:3px;"
                                         "border-style: solid;"
                                         "border-color: grey;"
                                         "background-color: rgb(255,255,255);}"
                                         "QPushButton:hover{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgb(175, 212, 245));"
                                         "border-color: rgb(135, 141, 155);}");
        if(!isShowBtn3)
            t_3_btn->hide();

        tilebarForMessageBox *t_tilebar = new tilebarForMessageBox;

        mainArea *t_mainArea = new mainArea;
        t_mainArea->setInfo(text);


        QLabel *t_icon =new QLabel;
        t_icon->setFixedSize(50, 50);
        t_icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        t_icon->setPixmap(icon);
        t_icon->setScaledContents(true);

        QHBoxLayout *t_1_hl = new QHBoxLayout;
        t_1_hl->setContentsMargins(10, 0, 1, 0);
        t_1_hl->setSpacing(0);
        t_1_hl->addWidget(t_icon);
        t_1_hl->addWidget(t_mainArea);


        QFrame* t_line = new QFrame;
        t_line->setFixedWidth(this->width()-2);
        t_line->setFrameShape(QFrame::HLine);
        t_line->setFrameShadow(QFrame::Sunken);


        QHBoxLayout *t_2_hl = new QHBoxLayout;
        t_2_hl->setContentsMargins(0, 0, 8, 7);
        t_2_hl->setSpacing(8);
        t_2_hl->addStretch();
        t_2_hl->addWidget(t_3_btn);
        t_2_hl->addWidget(m_2_btn);
        t_2_hl->addWidget(t_1_btn);

        t_mainArea->setContentsMargins(1, 0, 1, 0);
        QVBoxLayout *t_vl = new QVBoxLayout;
        t_vl->setMargin(0);
        t_vl->setSpacing(0);
        t_vl->addWidget(t_tilebar);
        t_vl->addLayout(t_1_hl);
        t_vl->addWidget(t_line, 0 ,Qt::AlignHCenter);
        t_vl->addSpacing(5);
        t_vl->addLayout(t_2_hl);

        this->setLayout(t_vl);

        connect(t_tilebar->m_close, SIGNAL(clicked()), this, SLOT(close()));
        connect(t_1_btn, SIGNAL(clicked()), this, SLOT(slot_CancelPressed()));
        connect(m_2_btn, SIGNAL(clicked()), this, SLOT(slot_OkPressed()));
        connect(t_3_btn, SIGNAL(clicked()), this, SLOT(slot_CoverPressed()));

    }

    void paintEvent(QPaintEvent *e)
    {
        Q_UNUSED(e);
        QPainter painter(this);
        painter.setPen(QColor(175, 212, 245));
        painter.drawRect(0, 0, this->width()-1, this->height()-1);
    }


    ~MessageBox()
    {

    }


    const Checked &getChecked()
    {
        return m_checked;
    }

signals:

private slots:
    void slot_OkPressed()
    {
        m_checked = Ok;
        close();
    }

    void slot_CancelPressed()
    {
        m_checked = Cancel;
        close();
    }

    void slot_CoverPressed()
    {
        m_checked = Cover;
        close();
    }

private:
    Checked m_checked;
};


#endif // MESSAGEBOX_H

