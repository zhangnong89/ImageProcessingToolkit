#ifndef APPDEFINE
#define APPDEFINE

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QStyleOption>
#include <QStyle>
#include <QPainter>
#include <QScrollArea>
#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>

#include <QPushButton>

#include <QDir>
#include <QFileDialog>
#include <QObject>
#include <QPoint>
#include <QRect>
#include <QWidget>
#include <QStackedWidget>
#include <QScrollArea>
#include <QGraphicsView>
#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QFileInfo>
#include <QLineEdit>
#include<QThread>

//opencv
//#include<opencv/cv.h>
#include<opencv/cv.hpp>

//linux system
#include<math.h>

#define MARGIN 5     //感应鼠标的宽度
#define MIN_H 305    //窗口最小高度
#define MIN_W 505    //窗口最小宽度
#define WIN_W 950*1.125/*1425*/    //初始窗口宽
#define WIN_H 580*1.125/*870*/    //初始窗口高
#define SIDEMENUBAR_W 170   //侧边栏宽



//local head file
#include"bottommenu.h"
#include"dragproxy.h"
#include"initpage.h"
#include"mainarea.h"
#include"mainpage.h"
#include"menu.h"
#include"messagebox.h"
#include"pictureview.h"
#include"titlebar.h"
#include"topmenubar.h"
#include"widget.h"
#include"undertopmenubar.h"
#include"puzzlesetting.h"
#include"advancesetting.h"
#include"basicsetting.h"
#include"pictureproperties.h"
#include"cellitem.h"
#include"exifInfo.h"
#include"picturegraphicsitem.h"
#include"mat2qimage.h"
#include"pictureshotdialog.h"
#include"cutdialog.h"
#include"adjustsizedialog.h"
#include"picturemosaic.h"
#include"pictureformatconvert.h"
#include"picturefilter.h"
#include"picturethread.h"
#include"stacklist.h"
#include"comparepage.h"
#include"picturepuzzle.h"
#include"picturepuzzlewidget.h"
#include"picturestackedwidget.h"

#endif // APPDEFINE

