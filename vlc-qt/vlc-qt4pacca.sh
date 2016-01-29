#!/bin/bash
rm -rf build
mkdir -p build
cd build

cmake .. -DCMAKE_INSTALL_PREFIX=osx -DQt5Core_DIR=/Applications/Qt/5.4/5.4/clang_64/lib/cmake/Qt5Core -DQt5Quick_DIR=/Applications/Qt/5.4/5.4/clang_64/lib/cmake/Qt5Quick -DQt5Widgets_DIR=/Applications/Qt/5.4/5.4/clang_64/lib/cmake/Qt5Widgets/ -DLIBVLC_VERSION=0x020100

make
make install

mkdir -p osx/include

cp src/Config.h include/VLCQtCore
cp src/widgets/VLCQtWidgets.framework/Headers/WidgetSeek.h osx/include/
cp src/widgets/VLCQtWidgets.framework/Headers/SharedExportWidgets.h osx/include/
cp src/widgets/VLCQtWidgets.framework/Headers/WidgetVideo.h osx/include/
cp osx/lib/VLCQtCore.framework/VLCQtCore osx/lib/libvlc-qt.dylib
cp osx/lib/VLCQtWidgets.framework/VLCQtWidgets osx/lib/libvlc-qt-widgets.dylib
cp ../src/core/*.h include/

cd osx/include
ln -s ../../include/VLCQtCore vlc-qt
cd -
