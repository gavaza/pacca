

macx {
    LIBS += -L$$PWD/../vlc-qt/build/osx/lib -lvlc-qt -lvlc-qt-widgets
    LIBS += -L/opt/local/lib -lvlc
}
unix {
    LIBS += -L$$PWD/../vlc-qt/build/debian/lib -lvlc-qt -lvlc-qt-widgets
    LIBS += -L/usr/lib -lvlc
}
win32 {
    DEFINES += WIN32_DLL
    LIBS += -L$$PWD/../vlc-qt/build/windows/lib -lVLCQtCore -lVLCQtWidgets
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
    INCLUDEPATH += $$PWD/../vlc-qt/build/windows/include/VLCQtCore
    DEPENDPATH  += $$PWD/../vlc-qt/build/windows/include/VLCQtCore
    INCLUDEPATH += $$PWD/../vlc-qt/build/windows/include/VLCQtWidgets
    DEPENDPATH  += $$PWD/../vlc-qt/build/windows/include/VLCQtWidgets
    INCLUDEPATH += $$PWD/../vlc-qt/build/windows/include
    DEPENDPATH  += $$PWD/../vlc-qt/build/windows/include
    INCLUDEPATH += "C:/Program Files/VideoLAN/VLC/sdk/include"
    INCLUDEPATH += "C:/Program Files (x86)/VideoLAN/VLC/sdk/include"

    INCLUDEPATH += "C:/Users/ef9g/Programas/vlc/sdk/include" #EF9G
}
