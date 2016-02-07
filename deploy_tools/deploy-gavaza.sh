#!/bin/bash
# plugins

set -x
APP_NAME=${1}
LOCAL_PATH_=`pwd`
PACCA_GIT = ../../pacca-git

# change_install_name oldname newname file.dylib
change_install_name() {
  OLD="$1"
  NEW="$2"
  FILE="$3"

  OTOOL_OUT=$(otool -l "$FILE")
  echo "$OTOOL_OUT" | grep -q "$OLD"
  if [ ! $? -eq 0 ] ; then
    # Old name not present
    echo "$OTOOL_OUT" | grep -q "$NEW"
    if [ ! $? -eq 0 ] ; then
      # New name not present => error
      echo "[$SCRIPT] Error: no reference to '$OLD' found in '$FILE'"
#     exit 1
    fi
  else
    doo install_name_tool -change "$OLD" "$NEW" "$FILE"
  fi
}

doo(){
  echo "[$SCRIPT] $@"
  "$@"
}



mkdir -p ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks

#cp -f ${PACCA_GIT}/vlc-qt/build/osx/lib/libvlc-qt.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
#cp -f ${PACCA_GIT}/vlc-qt/build/osx/lib/libvlc-qt-widgets.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
cp -f ${PACCA_GIT}/vlc-qt/build/osx/lib/VLCQtCore.framework/VLCQtCore ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
cp -f ${PACCA_GIT}/vlc-qt/build/osx/lib/VLCQtWidgets.framework/VLCQtWidgets ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
cp -f /opt/local/lib/libvlc.5.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
cp -f /opt/local/lib/libvlc.5.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
cp -f ../lib/*.1.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
mkdir -p ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/
cp -f /opt/local/lib/graphviz/libgvplugin_pango.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/
cp -f /opt/local/lib/graphviz/libgvplugin_dot_layout.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/
cp -f /opt/local/lib/graphviz/config6 ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/

#cp -r ../Application/languages ${LOCAL_PATH_}/${APP_NAME}/Contents/Languages

wait

install_name_tool -id @executable_path/../Frameworks/libvlc.5.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc.5.dylib
install_name_tool -id @executable_path/../Frameworks/libvlc-qt.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
install_name_tool -id @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -id @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_dot_layout.6.dylib
install_name_tool -id @executable_path/../Frameworks/graphviz/libgvplugin_pango.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_pango.6.dylib

cd ../lib
#for i in *.1.dylib; do
#  install_name_tool -id $i "${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/$i"
#done

for i in *.1.dylib; do
   for j in *.1.dylib; do
       change_install_name $i @executable_path/../Frameworks/$i "${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/$j"
   done
   change_install_name $i @executable_path/../Frameworks/$i "${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca"
done

cd -


# libvlc
install_name_tool -change @loader_path/lib/libvlc.5.dylib @executable_path/../Frameworks/libvlc.5.dylib ${APP_NAME}/Contents/MacOS/Pacca

# libvlc-qt.dylib
version_libvlc="1.0.0"

install_name_tool -change @rpath/VLCQtCore.framework/Versions/${version_libvlc}/VLCQtCore @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/VLCQtCore.framework/Versions/${version_libvlc}/VLCQtCore @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
install_name_tool -change @rpath/VLCQtCore.framework/Versions/${version_libvlc}/VLCQtCore @executable_path/../Frameworks/libvlc-qt.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib

# libvlc-qt-widgets
install_name_tool -change @rpath/VLCQtWidgets.framework/Versions/${version_libvlc}/VLCQtWidgets @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/MacOS/Pacca
install_name_tool -change @rpath/VLCQtWidgets.framework/Versions/${version_libvlc}/VLCQtWidgets @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${APP_NAME}/Contents/Frameworks/libVideo.1.dylib

# graphviz
install_name_tool -change /opt/local/lib/graphviz/libgvplugin_dot_layout.6.dylib @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_dot_layout.6.dylib
install_name_tool -change /opt/local/lib/graphviz/libgvplugin_pango.6.dylib @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_pango.6.dylib

cd ${LOCAL_PATH_}
mkdir -p ${APP_NAME}/Contents/PlugIns/vlc
cp -r /opt/local/lib/vlc/plugins/ ${APP_NAME}/Contents/PlugIns/vlc/

macdeployqt ${LOCAL_PATH_}/${APP_NAME} -no-strip

echo sucess
