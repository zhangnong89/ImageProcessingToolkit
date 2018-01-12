#ifndef INITPAGE_H
#define INITPAGE_H
#include"all.h"

class Messagebox;
class InitPage : public QWidget
{
    Q_OBJECT

public:
    explicit InitPage(QWidget *parent = 0);
    QString openFileDialog(QWidget *_parent, const QString defaultDir);

    ~InitPage();

signals:
    void sig_openFile(QString fileName);        //点击“打开文件”发送此信号

public slots:
     void slot_OpenfileDialog();

private:

};

#endif // INITPAGE_H
