QT       += sql multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = DatabaseControl
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

HEADERS += \
    controlusers.h \
    controlsessions.h \
    controlspecies.h \
    controldictionary.h \
    dialogchoosespecie.h \
    dialogselectsession.h \
    controlsubject.h

SOURCES += \
    controlusers.cpp \
    controlsessions.cpp \
    controlspecies.cpp \
    controldictionary.cpp \
    dialogchoosespecie.cpp \
    dialogselectsession.cpp \
    controlsubject.cpp


FORMS += \
    controldictionary.ui \
    controlusers.ui \
    dialogchoosespecie.ui \
    controlsessions.ui \
    controlspecies.ui \
    dialogselectsession.ui \
    controlsubject.ui


LIBS += -L$$OUT_PWD/../lib -lDatabase
INCLUDEPATH += $$PWD/../Database

RESOURCES += ../Application/resource.qrc
