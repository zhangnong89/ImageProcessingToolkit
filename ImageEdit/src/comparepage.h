#ifndef COMPAREPAGE_H
#define COMPAREPAGE_H
#include"all.h"

class PictureView;
class ComparePage : public QWidget
{

    Q_OBJECT

public:
    explicit ComparePage(QWidget* parent = 0);
    ~ComparePage();

    PictureView* pictureView_1;
    PictureView* pictureView_2;
private:
    QString filePath;
    QString currentFilePath;

protected:
    void mousePressEvent();

signals:
    void sig_comparePressMouse();
public slots:
    void slot_receiveFirstImage(const QString&);
    void slot_receiveCurrentImage(const QString&);


};

#endif // COMPAREPAGE_H
