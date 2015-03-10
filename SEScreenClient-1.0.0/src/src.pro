

QT       += core gui network

CONFIG  += qxt static warn_on
QXT     += gui core


TARGET = SEScreenClient
TEMPLATE = app

DESTDIR = ../bin
MOC_DIR = ../build/moc
RCC_DIR = ../build/rcc
UI_DIR = ../build/ui
unix:OBJECTS_DIR = ../build/o/unix
win32:OBJECTS_DIR = ../build/o/win32
macx:OBJECTS_DIR = ../build/o/mac

SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    apiconnector.cpp \
    screendialog.cpp \
    clickablelabel.cpp \
    edit.cpp \
    lambdaconnect.cpp \
    gsc.cpp

HEADERS  += mainwindow.h \
    login.h \
    main.h \
    apiconnector.h \
    screendialog.h \
    clickablelabel.h \
    configuration.h \
    edit.h \
    lambdaconnect.h \
    gsc.h

FORMS    += mainwindow.ui \
    login.ui \
    screendialog.ui \
    edit.ui
QMAKE_CXXFLAGS += -std=gnu++11 -std=c++0x

RESOURCES += \
    res.qrc 
