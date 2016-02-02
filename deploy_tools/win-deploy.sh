#!/bin/bash

set -x

APP_NAME=Pacca.exe
VLC_DIR=/home/ef9g/Programas/vlc # EF9G
VLCQT_DIR=/home/ef9g/Nuevo/pacca-code/trunk/vlc-qt #EF9G
GRAPHVIZ_PATH=/home/ef9g/Programas/Graphviz2.38/bin #EF9G
OUTPUT_DIR=/home/ef9g/Nuevo/pacca-code/build-Pacca-Desktop_Qt_5_4_1_MinGW_32bit-Release/bin #EF9G
PROGRAM_FILES="/cygdrive/c/Program Files (x86)"

cd  ${OUTPUT_DIR}
windeployqt ${APP_NAME}
cd -

# Graphviz library
cp -f ${GRAPHVIZ_PATH}/cgraph.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/gvc.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/zlib1.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/cdt.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/Pathplan.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/libexpat.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/ltdl.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/config6 ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/gvplugin_core.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/gvplugin_dot_layout.dll ${OUTPUT_DIR}
#cp -f ${GRAPHVIZ_PATH}/gvplugin_gd.dll ${OUTPUT_DIR}
#cp -f ${GRAPHVIZ_PATH}/gvplugin_gdiplus.dll ${OUTPUT_DIR}
#cp -f ${GRAPHVIZ_PATH}/gvplugin_neato_layout.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/gvplugin_pango.dll ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/libglib-2.0-0.dll ${OUTPUT_DIR}


# VLC-Qt library
cp -f ${VLCQT_DIR}/build/windows/bin/libVLCQtCore.dll ${OUTPUT_DIR}
cp -f ${VLCQT_DIR}/build/windows/bin/libVLCQtWidgets.dll ${OUTPUT_DIR}
cp -f ${VLCQT_DIR}/build/windows/bin/libvlc.dll ${OUTPUT_DIR}
cp -f ${VLCQT_DIR}/build/windows/bin/libvlccore.dll ${OUTPUT_DIR}



# Internet Explorer library
#cp -f "${PROGRAM_FILES}/Internet Explorer/IEShims.dll" ${OUTPUT_DIR}

# VLC plugins
# cp -r ${VLC_DIR}/plugins ${OUTPUT_DIR}
cp -f ${VLCQT_DIR}/build/windows/bin/plugins ${OUTPUT_DIR}
