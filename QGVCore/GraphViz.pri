#GraphViz librairie
DEFINES += WITH_CGRAPH
INCLUDEPATH += private
QMAKE_CXXFLAGS += -DQGVCORE_LIB


macx{
 LIBS += -L/opt/local/lib -lcdt -lgvc -lcgraph
 INCLUDEPATH += /opt/local/include/graphviz
}
unix {
# CONFIG += link_pkgconfig
# PKGCONFIG += libcdt libgvc libcgraph libgraph
 LIBS += -L/usr/lib/graphviz -L/usr/lib/ -lcdt -lgvc -lcgraph
# LIBS += -L/sw/lib -lgraph
 INCLUDEPATH += /usr/include/graphviz
}
win32 {
 #Configure Windows GraphViz path here :
 GRAPHVIZ_PATH = "C:\Program Files\Graphviz2.38"

 DEFINES += WIN32_DLL
 DEFINES += GVDLL
 INCLUDEPATH += $$GRAPHVIZ_PATH/include/graphviz
 LIBS += -L$$GRAPHVIZ_PATH/lib/release/dll -lgvc -lcgraph -lcdt

 GRAPHVIZ_PATH_X64 = "C:\Program Files (x86)\Graphviz2.38"
 INCLUDEPATH += $$GRAPHVIZ_PATH_X64/include/graphviz
 LIBS += -L$$GRAPHVIZ_PATH_X64/lib/release/dll -lgvc -lcgraph -lcdt

 GRAPHVIZ_PATH = "C:\Users\ef9g\Programas\Graphviz2.38" # EF9G
 INCLUDEPATH += $$GRAPHVIZ_PATH/include/graphviz # EF9G
 LIBS += -L$$GRAPHVIZ_PATH/lib/release/dll -lgvc -lcgraph -lcdt #EF9G
}
