#-------------------------------------------------
#
# Project created by QtCreator 2013-04-17T09:06:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graph
TEMPLATE = lib

DEFINES += GRAPH_LIBRARY

DESTDIR = $$OUT_PWD/../../lib
DLLDESTDIR = $$OUT_PWD/../../bin

#QGVCore librairie
LIBS += -L$$OUT_PWD/../../lib -lGraphWindowCore
INCLUDEPATH += $$PWD/../GraphWindowCore
DEPENDPATH += $$PWD/../GraphWindowCore

INCLUDEPATH += $$PWD/../QGVCore
DEPENDPATH += $$PWD/../QGVCore


#GraphViz librairie
#!include(../QGVCore/GraphViz.pri) {
#     error("fail open GraphViz.pri")
#}

SOURCES +=\
    graph.cpp \

HEADERS  += \
    graph.h \
