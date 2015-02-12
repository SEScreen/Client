#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T23:50:26
#
#-------------------------------------------------



QT       += core gui svg network

CONFIG  += qxt
QXT     += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SEScreenClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    apiconnector.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES += icon.png

RESOURCES += \
    res.qrc
