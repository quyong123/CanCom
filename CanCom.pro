#-------------------------------------------------
#
# Project created by QtCreator 2018-03-02T14:56:03
#
#-------------------------------------------------

QT       += core gui
LIBS+= -lqwt
INCLUDEPATH +=D:\Qt\Qt5.6.3\5.6.3\mingw49_32\include\qwt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CanCom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectdialog.cpp \
    candevice.cpp \
    udsform.cpp \
    ccpform.cpp \
    canringbuff.cpp \
    ccpproc.cpp \
    bsptestform.cpp \
    hmiproc.cpp

HEADERS  += mainwindow.h \
    connectdialog.h \
    candevice.h \
    config.h \
    udsform.h \
    ccpform.h \
    canringbuff.h \
    ccpproc.h \
    ccpparam.h \
    myhelper.h \
    bsptestform.h \
    hmiproc.h

FORMS    += mainwindow.ui \
    connectdialog.ui \
    udsform.ui \
    ccpform.ui \
    bsptestform.ui
LIBS +=-LD:\QtApp\CanCom\CanCom -lControlCAN
