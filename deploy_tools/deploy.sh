#!/bin/bash
# plugins

set -x

APP_NAME=${1}
LOCAL_PATH_=`pwd`

mkdir -p ${APP_NAME}/Contents/Frameworks

cp -f ../../trunk/vlc-qt/build/osx/lib/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../../trunk/vlc-qt/build/osx/lib/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libQGVCore.1.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libGraphWindow.1.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libPhylogenetic.1.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libStatistics.1.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libDatabase.1.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libDatabaseControl.1.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libVideo.1.dylib ${APP_NAME}/Contents/Frameworks/ &
cp -f ../lib/libPlotWindow.1.dylib ${APP_NAME}/Contents/Frameworks/ &
mkdir -p ${APP_NAME}/Contents/Frameworks/graphviz/
cp -f /opt/local/lib/graphviz/libgvplugin_pango.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/ &
cp -f /opt/local/lib/graphviz/libgvplugin_dot_layout.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/ &
cp -f /opt/local/lib/graphviz/config6 ${APP_NAME}/Contents/Frameworks/graphviz/ &

wait

install_name_tool -id @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
install_name_tool -id @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -id @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_dot_layout.6.dylib
install_name_tool -id @executable_path/../Frameworks/graphviz/libgvplugin_pango.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_pango.6.dylib
install_name_tool -change @rpath/libvlc-qt.0.10.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt-widgets.0.10.dylib @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/libvlc-qt-widgets.0.10.dylib @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change @rpath/libvlc-qt.0.10.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -change @rpath/libvlc-qt.0.10.dylib @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
install_name_tool -change /opt/local/lib/graphviz/libgvplugin_dot_layout.6.dylib @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_dot_layout.6.dylib
install_name_tool -change /opt/local/lib/graphviz/libgvplugin_pango.6.dylib @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_pango.6.dylib

mkdir -p ${APP_NAME}/Contents/PlugIns/vlc
cp -r /Applications/VLC.app/Contents/MacOS/plugins/lib* ${APP_NAME}/Contents/PlugIns/vlc

cd ${APP_NAME}/Contents/PlugIns/vlc
for i in *; do
	install_name_tool -change @loader_path/../lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${i}
	install_name_tool -change /usr/lib/libiconv.2.dylib @executable_path/../Frameworks/libiconv.2.dylib ${i}
done

cd ${LOCAL_PATH_}
macdeployqt ${APP_NAME}

echo sucess
