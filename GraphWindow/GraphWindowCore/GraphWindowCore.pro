#-------------------------------------------------
#
# Project created by QtCreator 2013-04-17T09:06:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphWindow
TEMPLATE = lib

DEFINES += GRAPHWINDOW_LIBRARY

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

#QGVCore librairie
LIBS += -L$$OUT_PWD/../lib -lQGVCore
INCLUDEPATH += $$PWD/../QGVCore
DEPENDPATH += $$PWD/../QGVCore


#GraphViz librairie
!include(../QGVCore/GraphViz.pri) {
     error("fail open GraphViz.pri")
 }

SOURCES +=\
    QGraphicsViewEc.cpp \
    graph.cpp \
    GraphWindow.cpp

HEADERS  += \
    QGraphicsViewEc.h \
    GraphWindow.h \
    graph.h \
    graphwindow_global.h

FORMS    += \
    GraphWindow.ui

RESOURCES += $$PWD/../../Application/resource.qrc
