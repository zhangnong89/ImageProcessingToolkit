#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T16:27:21
#
#-------------------------------------------------

QT       += core gui widgets
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picture-editor
TEMPLATE = app

QMAKE_RPATHDIR += /usr/share/picture-editor/lib

UI_DIR += forms
RCC_DIR += qrc
MOC_DIR += moc
OBJECTS_DIR += obj

SOURCES += main.cpp\
        widget.cpp \
    dragproxy.cpp \
    titlebar.cpp \
    mainarea.cpp \
    initpage.cpp \
    mainpage.cpp \
    pictureview.cpp \
    menu.cpp \
    bottommenu.cpp \
    topmenubar.cpp \
    undertopmenubar.cpp \
    puzzlesetting.cpp \
    advancesetting.cpp \
    basicsetting.cpp \
    pictureproperties.cpp \
    cellitem.cpp \
    exifInfo.cpp \
    picturegraphicsitem.cpp \
    mat2qimage.cpp \
    pictureshotdialog.cpp \
    cutdialog.cpp \
    adjustsizedialog.cpp \
    stacklist.cpp \
    picturemosaic.cpp \
    pictureformatconvert.cpp \
    picturefilter.cpp \
    comparepage.cpp \
    picturepuzzle.cpp \
    picturepuzzlewidget.cpp \
    picturestackedwidget.cpp

HEADERS  += widget.h \
    dragproxy.h \
    titlebar.h \
    mainarea.h \
    initpage.h \
    mainpage.h \
    pictureview.h \
    menu.h \
    messagebox.h \
    bottommenu.h \
    all.h \
    topmenubar.h \
    undertopmenubar.h \
    puzzlesetting.h \
    advancesetting.h \
    basicsetting.h \
    pictureproperties.h \
    cellitem.h \
    exifInfo.h \
    picturegraphicsitem.h \
    mat2qimage.h \
    pictureshotdialog.h \
    cutdialog.h \
    adjustsizedialog.h \
    stacklist.h \
    picturemosaic.h \
    pictureformatconvert.h \
    picturefilter.h \
    picturethread.h \
    comparepage.h \
    picturepuzzle.h \
    picturepuzzlewidget.h \
    picturestackedwidget.h

RESOURCES += \
    images.qrc

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2
LIBS +=-L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += glib-2.0
unix: PKGCONFIG += GraphicsMagick++
