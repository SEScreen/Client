#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T23:50:26
#
#-------------------------------------------------



QT       += core gui svg network

#CONFIG  += qxt
#QXT     += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = SEScreenClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    apiconnector.cpp \
    screendialog.cpp \
    clickablelabel.cpp

HEADERS  += mainwindow.h \
    login.h \
    main.h \
    apiconnector.h \
    screendialog.h \
    clickablelabel.h

FORMS    += mainwindow.ui \
    login.ui \
    screendialog.ui
