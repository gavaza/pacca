#!/bin/bash
# plugins

APP_NAME=${1}

macdeployqt ${APP_NAME} &
mkdir -p ${APP_NAME}/Contents/Frameworks
cp ../../trunk/vlc-qt/build/prefix/lib/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/
cp ../../trunk/vlc-qt/build/prefix/lib/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/lib* ${APP_NAME}/Contents/Frameworks/

install_name_tool -id @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
install_name_tool -id @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -id @executable_path/../Frameworks/libGraphWindow.1.dylib ${APP_NAME}/Contents/Frameworks/libGraphWindow.1.dylib

install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt-widgets.dylib @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib

wait

macdeployqt ${APP_NAME} -always-overwrite &

echo sucess
