QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PlotWindow
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

HEADERS += \
    qcustomplot.h \
    plotwindow.h \
    plotwindow_global.h

DEFINES += PLOTWINDOW_LIBRARY

SOURCES += \
    qcustomplot.cpp \
    plotwindow.cpp

FORMS    += plotwindow.ui

RESOURCES += $$PWD/../Application/resource.qrc
