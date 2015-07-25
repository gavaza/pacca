QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Phylogenetic
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

HEADERS += \
    phylogenetic.h

SOURCES += \
    phylogenetic.cpp

LIBS += -L$$OUT_PWD/../lib/ -lStatistics
INCLUDEPATH += $$PWD/../Statistics

FORMS +=

RESOURCES += ../Application/resource.qrc
