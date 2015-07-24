QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PlotWindow
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

HEADERS += \
    qcustomplot.h \
    plotwindow.h

SOURCES += \
    qcustomplot.cpp \
    plotwindow.cpp

FORMS    += plotwindow.ui

RESOURCES += ../Application/resource.qrc
