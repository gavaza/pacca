TARGET = Video
TEMPLATE = lib

DEFINES += VIDEO_LIBRARY

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

#Video librairie
!include(Video.pri) {
     error("fail open Video.pri")
}

HEADERS += \
    videowindow.h

SOURCES += \
    videowindow.cpp

FORMS += \
    videowindow.ui
