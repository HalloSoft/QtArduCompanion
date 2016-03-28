#-------------------------------------------------
#
# QtArduCompanion
# ScarySoft 2016
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
    mainwidget.cpp \
    arducontrolwindow.cpp \
    pincontrolrow.cpp

HEADERS +=\
    fdevice.h \
    util.h \
    mainwidget.h \
    qfirmata_global.h \
    qfirmata.h \
    arducontrolwindow.h \
    pincontrolrow.h

FORMS += \
    mainwidget.ui \
    arducontrolwindow.ui

