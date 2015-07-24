QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

LIBS += -L$$OUT_PWD/../lib -lDatabase
INCLUDEPATH += $$PWD/../Database

macx {
    LIBS += -L$$PWD/../../trunk/vlc-qt/build/osx/lib -lvlc-qt -lvlc-qt-widgets
    LIBS += -L/opt/local/lib -lvlc
}
unix {
    LIBS += -L$$PWD/../../trunk/vlc-qt/build/debian/lib -lvlc-qt -lvlc-qt-widgets
    LIBS += -L/usr/lib -lvlc
}
win32 {
    DEFINES += WIN32_DLL
    LIBS += -L$$PWD/../../trunk/vlc-qt/build/windows/lib -lvlc-qt -lvlc-qt-widgets
    LIBS += -L"C:/Program Files/VideoLAN/VLC" -lvlc
    LIBS += -L"C:/Program Files (x86)/VideoLAN/VLC" -lvlc

    LIBS += -L"C:\Users\ef9g\Programas\vlc" -lvlc #EF9G
}

macx {
    INCLUDEPATH += $$PWD/../../trunk/vlc-qt/build/osx/include/vlc-qt
    INCLUDEPATH += /opt/local/include
}
unix {
    INCLUDEPATH += $$PWD/../../trunk/vlc-qt/build/debian/include/vlc-qt
    INCLUDEPATH += /usr/include
}
win32 {
    INCLUDEPATH += $$PWD/../../trunk/vlc-qt/build/windows/include/vlc-qt
    DEPENDPATH  += $$PWD/../../trunk/vlc-qt/build/windows/include/vlc-qt
    INCLUDEPATH += "C:/Program Files/VideoLAN/VLC/sdk/include"
    INCLUDEPATH += "C:/Program Files (x86)/VideoLAN/VLC/sdk/include"

    INCLUDEPATH += "C:\Users\ef9g\Programas\vlc\sdk\include" #EF9G
}
