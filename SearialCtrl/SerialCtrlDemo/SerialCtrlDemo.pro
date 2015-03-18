#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T13:33:52
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialCtrlDemo
TEMPLATE = app


SOURCES += main.cpp\
        ComPortTestWgt.cpp


HEADERS  += ComPortTestWgt.h

FORMS    += ComPortTestWgt.ui

INCLUDEPATH += ./ \
               ../LibSerialCtrl

CONFIG(debug, debug|release) {
    DESTDIR = ../bin-debug
    LIBS += -L../bin-debug -lLibSerialCtrl
} else {
    DESTDIR = ../bin-release
    LIBS += -L../bin-release -lLibSerialCtrl
}

