#!/bin/bash

set -x

APP_NAME=Pacca.exe
VLC_DIR=/home/ef9g/Programas/vlc # EF9G
VLCQT_DIR=/home/ef9g/Nuevo/pacca-git/vlc-qt #EF9G
GRAPHVIZ_PATH=/home/ef9g/Programas/Graphviz2.38/bin #EF9G
OUTPUT_DIR=/home/ef9g/Nuevo/build-Pacca-Desktop_Qt_5_4_1_MinGW_32bit-Release/bin #EF9G
PROGRAM_FILES="/cygdrive/c/Program Files (x86)"
QT_DIR=/home/ef9g/Programas/Qt/Qt5.4.1/5.4/mingw491_32

cd  ${OUTPUT_DIR}
BASS_PATH=`pwd`/../../pacca-git/bass
windeployqt --release ${APP_NAME}
cd -

# Graphviz library
cp -f ${GRAPHVIZ_PATH}/config6 ${OUTPUT_DIR}
cp -f ${GRAPHVIZ_PATH}/*.dll ${OUTPUT_DIR}


# VLC-Qt library
cp -f ${VLCQT_DIR}/build/windows/bin/libVLCQtCore.dll ${OUTPUT_DIR}
cp -f ${VLCQT_DIR}/build/windows/bin/libVLCQtWidgets.dll ${OUTPUT_DIR}
cp -f ${VLCQT_DIR}/build/windows/bin/libvlc.dll ${OUTPUT_DIR}
cp -f ${VLCQT_DIR}/build/windows/bin/libvlccore.dll ${OUTPUT_DIR}



# Internet Explorer library
#cp -f "${PROGRAM_FILES}/Internet Explorer/IEShims.dll" ${OUTPUT_DIR}

# VLC plugins
# cp -r ${VLC_DIR}/plugins ${OUTPUT_DIR}
cp -rf ${VLCQT_DIR}/build/windows/bin/plugins ${OUTPUT_DIR}/plugins

# Bass plugin
cp -f ${BASS_PATH}/build/windows/lib/bass.dll ${OUTPUT_DIR}

# QtXlsx
cp -f ${QT_DIR}/bin/Qt5Xlsx.dll ${OUTPUT_DIR}

# QtPrintSupport
cp -f ${QT_DIR}/bin/Qt5PrintSupport.dll ${OUTPUT_DIR}
