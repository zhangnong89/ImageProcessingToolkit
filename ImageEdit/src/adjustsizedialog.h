#ifndef ADJUSTSIZEDIALOG
#define ADJUSTSIZEDIALOG

#include"all.h"
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class AdjustSizeDialog : public QDialog
{
        Q_OBJECT

public:
        AdjustSizeDialog(QWidget *parent = 0);
        ~AdjustSizeDialog();
        QLineEdit*wInput;
        QLineEdit*hInput;

        QPushButton*okBtn;
        QPushButton*cancelBtn;

signals:

public slots:
         void wInputChanged(QString fileName);
         void hInputChanged(QString fileName);
private:
        QLabel*wLabel;
        QLabel*hLabel;

        QLabel*wPixLabel;
        QLabel*hPixLabel;
        QCheckBox*lockRatio;
};

#endif // ADJUSTSIZEDIALOG

