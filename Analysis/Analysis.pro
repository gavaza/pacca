#-------------------------------------------------
#
# Project created by QtCreator 2016-01-31T10:24:54
#
#-------------------------------------------------

QT       += core sql gui multimediawidgets multimedia xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Analysis
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

DEFINES += ANALYSIS_LIBRARY

SOURCES += analysis.cpp \
    dialogconfigstats.cpp \
    viewtablestats.cpp \
    viewgraphicstats.cpp


HEADERS += analysis.h\
    dialogconfigstats.h \
    viewtablestats.h \
        analysis_global.h \
    viewgraphicstats.h

FORMS += analysis.ui \
       viewtablestats.ui \
     dialogconfigstats.ui \
    viewgraphicstats.ui

LIBS += -L$$OUT_PWD/../lib/ -lGraph -lGraphWindowCore -lStatistics -lPhylogenetic -lDatabaseControl -lPlotWindow  -lDatabase

INCLUDEPATH += $$PWD/../Database
INCLUDEPATH += $$PWD/../DatabaseControl
INCLUDEPATH += $$PWD/../Phylogenetic
INCLUDEPATH += $$PWD/../Statistics
INCLUDEPATH += $$PWD/../PlotWindow
INCLUDEPATH += $$PWD/../GraphWindow/Graph
INCLUDEPATH += $$PWD/../GraphWindow/GraphWindowCore
INCLUDEPATH += $$PWD/../GraphWindow/QGVCore


