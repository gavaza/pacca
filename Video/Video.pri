QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

LIBS += -L$$OUT_PWD/../lib -lDatabase
INCLUDEPATH += $$PWD/../Database

macx {
    LIBS += -L$$PWD/../vlc-qt/build/osx/lib -lvlc-qt -lvlc-qt-widgets
#    LIBS += -F$$PWD/../vlc-qt/build/osx/lib/ -framework VLCQtCore
#    LIBS += -F$$PWD/../vlc-qt/build/osx/lib/ -framework VLCQtWidgets
    LIBS += -L/opt/local/lib -lvlc
}
unix {
    LIBS += -L$$PWD/../vlc-qt/build/debian/lib -lvlc-qt -lvlc-qt-widgets
    LIBS += -L/usr/lib -lvlc
}
win32 {
    DEFINES += WIN32_DLL
    LIBS += -L$$PWD/../vlc-qt/build/windows/lib -lvlc-qt -lvlc-qt-widgets
    LIBS += -L"C:/Program Files/VideoLAN/VLC" -lvlc
    LIBS += -L"C:/Program Files (x86)/VideoLAN/VLC" -lvlc

    LIBS += -L"C:\Users\ef9g\Programas\vlc" -lvlc #EF9G
}

macx {
    INCLUDEPATH += $$PWD/../vlc-qt/build/include
    INCLUDEPATH += $$PWD/../vlc-qt/build/osx/include
    INCLUDEPATH += /opt/local/include
}
unix {
    INCLUDEPATH += $$PWD/../vlc-qt/build/debian/include/vlc-qt
    INCLUDEPATH += /usr/include
}
win32 {
    INCLUDEPATH += $$PWD/../vlc-qt/build/windows/include/vlc-qt
    DEPENDPATH  += $$PWD/../vlc-qt/build/windows/include/vlc-qt
    INCLUDEPATH += "C:/Program Files/VideoLAN/VLC/sdk/include"
    INCLUDEPATH += "C:/Program Files (x86)/VideoLAN/VLC/sdk/include"

    INCLUDEPATH += "C:\Users\ef9g\Programas\vlc\sdk\include" #EF9G
}
