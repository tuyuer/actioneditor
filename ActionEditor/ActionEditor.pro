#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T09:05:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActionEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newactiondialog.cpp \
    action.cpp \
    listwidget.cpp \
    frameview.cpp \
    paintview.cpp \
    collisiondot.cpp \
    editcollisiondotdialog.cpp \
    frameinfo.cpp

HEADERS  += mainwindow.h \
    newactiondialog.h \
    action.h \
    listwidget.h \
    frameview.h \
    paintview.h \
    collisiondot.h \
    editcollisiondotdialog.h \
    frameinfo.h

FORMS    += mainwindow.ui \
    newactiondialog.ui \
    editcollisiondotdialog.ui

RESOURCES += \
    UI.qrc
