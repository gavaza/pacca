TARGET = Video
TEMPLATE = lib

DEFINES += VIDEO_LIBRARY

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

HEADERS += \
    videowindow.h

SOURCES += \
    videowindow.cpp

FORMS += \
    videowindow.ui

RESOURCES += $$PWD/../Application/resource.qrc

QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

LIBS += -L$$OUT_PWD/../lib -lDatabase
INCLUDEPATH += $$PWD/../Database

#Video librairie
!include(Video.pri) {
     error("fail open Video.pri")
}
