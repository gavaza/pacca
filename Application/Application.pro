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

SOURCES += main.cpp\
        mainwindow.cpp \
    dialoglogin.cpp \
    dialogchoosedict.cpp \
    dialogchooselanguage.cpp

HEADERS  += mainwindow.h \
    dialoglogin.h \
    dialogchoosedict.h \
    dialogchooselanguage.h

FORMS    += mainwindow.ui \
    dialoglogin.ui \
    dialogchoosedict.ui \
    dialogchooselanguage.ui

RESOURCES += \
    resource.qrc

LIBS += -L$$OUT_PWD/../lib/ -lVideo -lText -lAnalysis -lDatabaseControl -lDatabase


INCLUDEPATH += $$PWD/../Text
INCLUDEPATH += $$PWD/../Analysis
INCLUDEPATH += $$PWD/../DatabaseControl
INCLUDEPATH += $$PWD/../Video

# verify soon below
INCLUDEPATH += $$PWD/../PlotWindow
INCLUDEPATH += $$PWD/../Statistics
INCLUDEPATH += $$PWD/../GraphWindow/GraphWindowCore
INCLUDEPATH += $$PWD/../GraphWindow/QGVCore
INCLUDEPATH += $$PWD/../Phylogenetic
INCLUDEPATH += $$PWD/../Database

#Video librairie
!include(../Video/Video.pri) {
     error("fail open Video.pri")
}



