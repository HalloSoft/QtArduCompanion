#-------------------------------------------------
#
# QtArduCompanion
# ScarySoft 2016
#
#-------------------------------------------------
CONFIG += c++11

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
    pincontrolrow.cpp \
    inputwidget.cpp \
    outputwidget.cpp

HEADERS +=\
    fdevice.h \
    util.h \
    mainwidget.h \
    qfirmata_global.h \
    qfirmata.h \
    arducontrolwindow.h \
    pincontrolrow.h \
    inputwidget.h \
    outputwidget.h

FORMS += \
    mainwidget.ui \
    arducontrolwindow.ui \
    inputwidget.ui \
    outputwidget.ui

RESOURCES += \
    icons.qrc

