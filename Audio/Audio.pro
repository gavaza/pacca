#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T13:20:14
#
#-------------------------------------------------

TARGET = Audio
TEMPLATE = lib

QT -= core gui

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

DEFINES += AUDIO_LIBRARY

HEADERS += audio.h \

SOURCES += \
    audio.cpp

#Video librairie
!include(Audio.pri) {
     error("fail open Audio.pri")
}
