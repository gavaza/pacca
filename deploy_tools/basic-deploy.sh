#!/bin/bash
# plugins

APP_NAME=${1}
LOCAL_PATH_=`pwd`

mkdir -p ${APP_NAME}/Contents/Frameworks
cp ../../vlc-qt/build/prefix/lib/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/
cp ../../vlc-qt/build/prefix/lib/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/
cp -r ../../Application/languages ${APP_NAME}/Contents/Languages
cp -f ../lib/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libGraphWindow.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libPhylogenetic.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libStatistics.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libDatabaseControl.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libVideo.1.dylib ${APP_NAME}/Contents/Frameworks/


install_name_tool -id @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
install_name_tool -id @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -id @executable_path/../Frameworks/libGraphWindow.1.dylib ${APP_NAME}/Contents/Frameworks/libGraphWindow.1.dylib
install_name_tool -id @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/libQGVCore.1.dylib
install_name_tool -id @executable_path/../Frameworks/libStatistics.1.dylib ${APP_NAME}/Contents/Frameworks/libStatistics.1.dylib
install_name_tool -id @executable_path/../Frameworks/libPhylogenetic.1.dylib ${APP_NAME}/Contents/Frameworks/libPhylogenetic.1.dylib
install_name_tool -id @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/libDatabase.1.dylib
install_name_tool -id @executable_path/../Frameworks/libDatabaseControl.1.dylib ${APP_NAME}/Contents/Frameworks/libDatabaseControl.1.dylib
install_name_tool -id @executable_path/../Frameworks/libVideo.1.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib

install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt-widgets.dylib @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -change libGraphWindow.1.dylib @executable_path/../Frameworks/libGraphWindow.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libQGVCore.1.dylib @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libQGVCore.1.dylib @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/libGraphWindow.1.dylib
install_name_tool -change libQGVCore.1.dylib @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/libQGVCore.1.dylib
install_name_tool -change libStatistics.1.dylib @executable_path/../Frameworks/libStatistics.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libPhylogenetic.1.dylib @executable_path/../Frameworks/libPhylogenetic.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libDatabase.1.dylib @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libDatabase.1.dylib @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/libDatabaseControl.1.dylib
install_name_tool -change libDatabaseControl.1.dylib @executable_path/../Frameworks/libDatabaseControl.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libVideo.1.dylib @executable_path/../Frameworks/libVideo.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libDatabase.1.dylib @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change @rpath/libvlc-qt-widgets.dylib @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib

echo sucess
