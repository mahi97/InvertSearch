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
    terminaldockwidget.cpp \
    dataStructures/tree.cpp \
    dataStructures/bst.cpp \
    dataStructures/tst.cpp \
    dataStructures/trie.cpp

HEADERS  += mainwindow.h \
    tabdockwidget.h \
    terminaldockwidget.h \
    base.h \
    dataStructures/tree.h \
    dataStructures/bst.h \
    dataStructures/tst.h \
    dataStructures/trie.h \
    trees.h


OBJECTS_DIR = $$PWD/objs/
MOC_DIR = $$PWD/objs/

CONFIG += c++14

RESOURCES +=
