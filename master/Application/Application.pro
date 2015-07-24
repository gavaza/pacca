#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T16:22:54
#
#-------------------------------------------------

QT       += core sql gui multimediawidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Pacca
TEMPLATE = app
DESTDIR = $$OUT_PWD/../bin
ICON = $$PWD/icons/logo.icns

#Video librairie
!include(../Video/Video.pri) {
     error("fail open Video.pri")
}

SOURCES += main.cpp\
        mainwindow.cpp \
    analysis.cpp \
    qcustomplot.cpp \
    dialoglogin.cpp \
    dialogchoosedict.cpp \
    viewtablestats.cpp \
    dialogconfigstats.cpp \
    graph.cpp \
    dialogchooselanguage.cpp \
    viewphylogenetics.cpp

HEADERS  += mainwindow.h \
    analysis.h \
    qcustomplot.h \
    dialoglogin.h \
    dialogchoosedict.h \
    viewtablestats.h \
    dialogconfigstats.h \
    graph.h \
    dialogchooselanguage.h \
    viewphylogenetics.h

FORMS    += mainwindow.ui \
    analysis.ui \
    dialoglogin.ui \
    dialogchoosedict.ui \
    viewtablestats.ui \
    dialogconfigstats.ui \
    dialogchooselanguage.ui \
    viewphylogenetics.ui

RESOURCES += \
    resource.qrc

LIBS += -L$$OUT_PWD/../lib/ -lQGVCore -lGraphWindow -lStatistics -lPhylogenetic -lDatabaseControl -lVideo -lPlotWindow

INCLUDEPATH += $$PWD/../Statistics
INCLUDEPATH += $$PWD/../Phylogenetic
INCLUDEPATH += $$PWD/../DatabaseControl
INCLUDEPATH += $$PWD/../Video
INCLUDEPATH += $$PWD/../QGVCore
INCLUDEPATH += $$PWD/../GraphWindow
INCLUDEPATH += $$PWD/../Database
INCLUDEPATH += $$PWD/../PlotWindow


