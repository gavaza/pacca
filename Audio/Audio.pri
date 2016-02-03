win32 {
    DEFINES += WIN32_DLL
    LIBS += -L$$PWD/../bass/build/windows/lib -lbass -lcomdlg32 -lgdi32
    INCLUDEPATH += $$PWD/../bass/build/windows/include
    DEPENDPATH  += $$PWD/../bass/build/windows/include
}

macx {
    LIBS += -L$$PWD/../bass/build/osx/lib -lbass
    INCLUDEPATH += $$PWD/../bass/build/osx/include
    DEPENDPATH  += $$PWD/../bass/build/osx/include
}

linux {
    LIBS += -L$$PWD/../bass/build/linux/lib -lbass
    INCLUDEPATH += $$PWD/../bass/build/linux/include
    DEPENDPATH  += $$PWD/../bass/build/linux/include
}
