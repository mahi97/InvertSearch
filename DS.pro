#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T23:28:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DS
TEMPLATE = app

VPATH += $$PWD/src
SOURCES += main.cpp\
        mainwindow.cpp \
    tabdockwidget.cpp \
    terminaldockwidget.cpp \
    dataStructures/tree.cpp \
    dataStructures/bst.cpp \
    dataStructures/tst.cpp \
    dataStructures/trie.cpp \
    searchthread.cpp \
    dataStructures/linkedlist.cpp

HEADERS  += include/mainwindow.h \
    include/tabdockwidget.h \
    include/terminaldockwidget.h \
    include/base.h \
    include/dataStructures/tree.h \
    include/dataStructures/bst.h \
    include/dataStructures/tst.h \
    include/dataStructures/trie.h \
    include/trees.h \
    include/searchthread.h \
    include/dataStructures/linkedlist.h


INCLUDEPATH += $$PWD/include

OBJECTS_DIR = $$PWD/objs/
MOC_DIR = $$PWD/objs/

CONFIG += c++14

RESOURCES += \
    resource.qrc
