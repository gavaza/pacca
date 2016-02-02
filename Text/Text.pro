#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T13:20:14
#
#-------------------------------------------------

TARGET = Text
TEMPLATE = lib

QT       += sql multimediawidgets

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

DEFINES += TEXT_LIBRARY

SOURCES += text.cpp

HEADERS += text.h\
        text_global.h

LIBS += -L$$OUT_PWD/../lib -lDatabase
INCLUDEPATH += $$PWD/../Database
