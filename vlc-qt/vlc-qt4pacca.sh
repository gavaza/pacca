#!/bin/bash

set -ev

touch build
rm -rf build
mkdir -p build
cd build

QT_DIR=/Applications/Qt/5.5.1/5.5

cmake .. -DCMAKE_INSTALL_PREFIX=osx -DQt5Core_DIR=${QT_DIR}/clang_64/lib/cmake/Qt5Core -DQt5Quick_DIR=${QT_DIR}/clang_64/lib/cmake/Qt5Quick -DQt5Widgets_DIR=${QT_DIR}/clang_64/lib/cmake/Qt5Widgets/ -DLIBVLC_VERSION=0x020100

make
make install

exit
