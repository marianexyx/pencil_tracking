#-------------------------------------------------
#
# Project created by QtCreator 2015-02-03T23:16:38
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArduinoWallManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlreader.cpp

HEADERS  += mainwindow.h \
    xmlreader.h \
    posebodypartpoint.h

FORMS    += mainwindow.ui
