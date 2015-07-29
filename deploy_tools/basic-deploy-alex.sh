#!/bin/bash
# plugins

#set -x

APP_NAME=${1}
LOCAL_PATH_=`pwd`

mkdir -p ${APP_NAME}/Contents/Frameworks
cp ../../vlc-qt/build/osx/lib/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/
cp ../../vlc-qt/build/osx/lib/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/
cp -r ../../Application/languages ${APP_NAME}/Contents/Languages

cp /opt/local/lib/libvlccore.7.dylib ${APP_NAME}/Contents/Frameworks/
cp /opt/local/lib/libvlc.5.dylib ${APP_NAME}/Contents/Frameworks/
cp -r /opt/local/lib/graphviz ${APP_NAME}/Contents/Frameworks/

cp -f ../lib/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libGraphWindow.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libPhylogenetic.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libStatistics.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libDatabaseControl.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libVideo.1.dylib ${APP_NAME}/Contents/Frameworks/
cp -f ../lib/libPlotWindow.1.dylib ${APP_NAME}/Contents/Frameworks/

install_name_tool -id @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
install_name_tool -id @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -id @executable_path/../Frameworks/libvlc.5.dylib ${APP_NAME}/Contents/Frameworks/libvlc.5.dylib
install_name_tool -id @executable_path/../Frameworks/libvlccore.7.dylib ${APP_NAME}/Contents/Frameworks/libvlccore.7.dylib
install_name_tool -id @executable_path/../Frameworks/libGraphWindow.1.dylib ${APP_NAME}/Contents/Frameworks/libGraphWindow.1.dylib
install_name_tool -id @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/libQGVCore.1.dylib
install_name_tool -id @executable_path/../Frameworks/libStatistics.1.dylib ${APP_NAME}/Contents/Frameworks/libStatistics.1.dylib
install_name_tool -id @executable_path/../Frameworks/libPhylogenetic.1.dylib ${APP_NAME}/Contents/Frameworks/libPhylogenetic.1.dylib
install_name_tool -id @executable_path/../Frameworks/libPlotWindow.1.dylib ${APP_NAME}/Contents/Frameworks/libPlotWindow.1.dylib
install_name_tool -id @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/libDatabase.1.dylib
install_name_tool -id @executable_path/../Frameworks/libDatabaseControl.1.dylib ${APP_NAME}/Contents/Frameworks/libDatabaseControl.1.dylib
install_name_tool -id @executable_path/../Frameworks/libVideo.1.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change @loader_path/../lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${APP_NAME}/Contents/Frameworks/libvlc.5.dylib
install_name_tool -change @loader_path/../lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
install_name_tool -change @loader_path/../lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change @loader_path/../lib/libvlc.5.dylib @executable_path/../Frameworks/libvlc.5.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
install_name_tool -change @loader_path/lib/libvlc.5.dylib @executable_path/../Frameworks/libvlc.5.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change @loader_path/lib/libvlc.5.dylib @executable_path/../Frameworks/libvlc.5.dylib ${APP_NAME}/Contents/MacOS/Pacca

install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt-widgets.dylib @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt-widgets.dylib @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -change @rpath/libvlc-qt.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change libVideo.1.dylib @executable_path/../Frameworks/libVideo.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libGraphWindow.1.dylib @executable_path/../Frameworks/libGraphWindow.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libQGVCore.1.dylib @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libQGVCore.1.dylib @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/libGraphWindow.1.dylib
install_name_tool -change libQGVCore.1.dylib @executable_path/../Frameworks/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/libQGVCore.1.dylib
install_name_tool -change libStatistics.1.dylib @executable_path/../Frameworks/libStatistics.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libStatistics.1.dylib @executable_path/../Frameworks/libStatistics.1.dylib ${APP_NAME}/Contents/Frameworks/libPhylogenetic.1.dylib
install_name_tool -change libPlotWindow.1.dylib @executable_path/../Frameworks/libPlotWindow.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libPhylogenetic.1.dylib @executable_path/../Frameworks/libPhylogenetic.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libDatabaseControl.1.dylib @executable_path/../Frameworks/libDatabaseControl.1.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change libDatabase.1.dylib @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change libDatabase.1.dylib @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/libDatabaseControl.1.dylib
install_name_tool -change libDatabase.1.dylib @executable_path/../Frameworks/libDatabase.1.dylib ${APP_NAME}/Contents/MacOS/Pacca

mkdir -p ${APP_NAME}/Contents/PlugIns/vlc
cp /Applications/VLC.app/Contents/MacOS/plugins/lib* ${APP_NAME}/Contents/PlugIns/vlc
cd ${APP_NAME}/Contents/PlugIns/vlc
for i in *; do
	install_name_tool -change @loader_path/../lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${i}
	install_name_tool -change /usr/lib/libiconv.2.dylib @executable_path/../Frameworks/libiconv.2.dylib ${i}
done

cd ${LOCAL_PATH_}

#macdeployqt ${APP_NAME}

echo sucess
