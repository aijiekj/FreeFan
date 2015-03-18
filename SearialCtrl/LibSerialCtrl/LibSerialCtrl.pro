#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T20:26:26
#
#-------------------------------------------------

QT       -= gui
QT       += serialport widgets

TEMPLATE = lib
#CONFIG += staticlib

DEFINES += LIBSERIALCTRL_LIBRARY

SOURCES += \
    PSerialCtrl.cpp \
    PSerialCommand.cpp

HEADERS +=\
        libserialctrl_global.h \
    PSerialCtrl.h \
    PSerialCommand.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../bin-debug
    TARGET = LibSerialCtrld
} else {
    DESTDIR = ../bin-release
    TARGET = LibSerialCtrl
}
