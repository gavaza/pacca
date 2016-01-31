QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Phylogenetic
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

HEADERS += \
    viewphylogenetics.h \
    phylogenetic.h

SOURCES += \
    viewphylogenetics.cpp \
    phylogenetic.cpp

FORMS += viewphylogenetics.ui

LIBS += -L$$OUT_PWD/../lib/ -lStatistics
INCLUDEPATH += $$PWD/../Statistics

RESOURCES += $$PWD/../Application/resource.qrc
