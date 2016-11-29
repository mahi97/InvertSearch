#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T23:28:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabdockwidget.cpp \
    terminaldockwidget.cpp

HEADERS  += mainwindow.h \
    tabdockwidget.h \
    terminaldockwidget.h \
    base.h


OBJECTS_DIR = $$PWD/objs/
MOC_DIR = $$PWD/objs/

CONFIG += c++14

RESOURCES +=
