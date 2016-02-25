#-------------------------------------------------
#
# Project created by QtCreator 2012-05-04T18:10:33
#
#-------------------------------------------------

QT       += widgets serialport

TARGET = qtArduCompanion
TEMPLATE = app

DEFINES += FIRMATATOR_LIBRARY

SOURCES += \
    fdevice.cpp \
    util.cpp \
    main.cpp \
    mainwidget.cpp

HEADERS +=\
    firmatator_global.h \
    fdevice.h \
    firmatator.h \
    util.h \
    mainwidget.h

FORMS += \
    mainwidget.ui

