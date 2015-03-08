#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T23:50:26
#
#-------------------------------------------------



QT       += core gui network widgets

CONFIG  += qxt
QXT     += gui core


TARGET = SEScreenClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    apiconnector.cpp \
    screendialog.cpp \
    clickablelabel.cpp \
    edit.cpp

HEADERS  += mainwindow.h \
    login.h \
    main.h \
    apiconnector.h \
    screendialog.h \
    clickablelabel.h \
    configuration.h \
    edit.h

FORMS    += mainwindow.ui \
    login.ui \
    screendialog.ui \
    edit.ui
QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    res.qrc
