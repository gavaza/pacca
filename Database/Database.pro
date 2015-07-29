QT       += sql multimediawidgets

TARGET = Database
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

HEADERS += \
    action.h \
    states.h \
    users.h \
    species.h \
    sessions.h \
    events.h \
    database.h \
    dictionary.h \
    connections.h \
    subject.h


SOURCES += \
    action.cpp \
    states.cpp \
    users.cpp \
    species.cpp \
    sessions.cpp \
    events.cpp \
    database.cpp \
    dictionary.cpp \
    connections.cpp \
    subject.cpp


RESOURCES += ../Application/resource.qrc
