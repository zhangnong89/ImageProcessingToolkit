#ifndef TOPMENUBAR
#define TOPMENUBAR
#include"all.h"
class pictureProperties;
class CellItem;
/*******************上部菜单栏************************/
class TopMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit TopMenuBar(QWidget *parent = 0);

    QPushButton *btnOpenFile;//open file button
    QPushButton *btnSave;//save button
    QPushButton *btnSaveAs;//save as button

    QPushButton *btnStoreAction ;
    QPushButton *btnUndo;//undo button
    QPushButton *btnRedo ;//redo button
    QPushButton *btnReset ;//reset button
    QPushButton *btnCompare;//compare button
    QPushButton *btnAttribute;
    QPushButton *btnShare;//share button

    ~TopMenuBar();
    QString openFileDialog(QWidget *_parent, const QString defaultDir);//create a openfile dialog
    void paintEvent(QPaintEvent *e);//background color

signals:
    void sig_openFile(QString fileName);        //点击“打开文件”发送此信号
    void sig_initSlider();
//    void sig_openFile(QString fileName);        //点击“打开文件”发送此信号

public slots:
     void slot_OpenfileDialog();
     void slot_attributeDialog();
     void slot_initialFile(QString fileName);
private:
    pictureProperties*picProperties;
    CellItem *cellItem;
    QString currentFileName;
};

#endif // TOPMENUBAR

