#!/bin/bash
set -x

VLC_PATH=C:/Users/ef9g/Programas/vlc #ef9g

mkdir -p build
cd build

cmake .. -G "MinGW Makefiles" \
	-DCMAKE_INSTALL_PREFIX=windows \
	-DCMAKE_CXX_COMPILER=g++ \
	-DCMAKE_C_COMPILER=gcc \
	-DCMAKE_MAKE_PROGRAM=make \
	-DCMAKE_RC_COMPILER=windres \
	-DLIBVLC_LIBRARY=${VLC_PATH}/libvlc.dll \
	-DLIBVLC_INCLUDE_DIR=${VLC_PATH}/sdk/include \
	-DLIBVLCCORE_LIBRARY=${VLC_PATH}/libvlccore.dll

make
make install

exit 0
