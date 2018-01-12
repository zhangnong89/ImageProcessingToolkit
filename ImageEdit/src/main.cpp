#include "widget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheet(":/images/blue.css");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return -1;
    }
    qApp->setStyleSheet(styleSheet.readAll());

//obtain the profile;

    QDir*proDir = new QDir;
    bool exist = proDir->exists(QDir::homePath()+"/.local/nfspb");
    if(!exist)
    {
        proDir->mkdir(QDir::homePath()+"/.local/nfspb");
    }


    Widget w;
    w.show();
//    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
