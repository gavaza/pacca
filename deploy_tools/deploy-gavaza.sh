#!/bin/bash
# plugins

set -x
APP_NAME=${1}
LOCAL_PATH_=`pwd`
PACCA_GIT=/Users/gavaza/Nuevo/pacca-git

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
  else
    doo install_name_tool -change "$OLD" "$NEW" "$FILE"
  fi
}

doo(){
  echo "[$SCRIPT] $@"
  "$@"
}

deploy_plugins(){
	rm -rf ${LOCAL_PATH_}/${APP_NAME}/Contents/PlugIns/vlc

	cd ${LOCAL_PATH_}

	mkdir -p ${LOCAL_PATH_}/${APP_NAME}/Contents/PlugIns/vlc
	cp -r /opt/local/lib/vlc/plugins/ ${LOCAL_PATH_}/${APP_NAME}/Contents/PlugIns/vlc/

	for i in ${LOCAL_PATH_}/${APP_NAME}/Contents/PlugIns/vlc/*;
	do
		sh ${PACCA_GIT}/deploy_tools/osx_vlc_plugins_postprocess.sh ${i}
	done
}

# change_id_name newname file.dylib
change_id_name() {
  NEW="$1"
  FILE="$2"

  OTOOL_OUT=$(otool -D "$FILE")
  echo "$OTOOL_OUT" | grep loader_path
  if [ $? -eq 0 ] ; then
    doo install_name_tool -id "$NEW" "$FILE"
  fi
}

mkdir -p ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks

cp -f ${PACCA_GIT}/vlc-qt/build/osx/lib/VLCQtCore.framework/VLCQtCore ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
cp -f ${PACCA_GIT}/vlc-qt/build/osx/lib/VLCQtWidgets.framework/VLCQtWidgets ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
cp -f /opt/local/lib/libvlc.5.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
cp -f /opt/local/lib/libvlccore.7.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
cp -f ../lib/*.1.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/
mkdir -p ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/
cp -f /opt/local/lib/graphviz/libgvplugin_pango.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/
cp -f /opt/local/lib/graphviz/libgvplugin_dot_layout.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/
cp -f /opt/local/lib/graphviz/config6 ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/
cp -f ${PACCA_GIT}/bass/build/osx/lib/*.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/

#cp -r ../Application/languages ${LOCAL_PATH_}/${APP_NAME}/Contents/Languages

wait

for i in ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/*.dylib; do
	LIB=$(echo $i | grep '\(lib[A-z]..*\.dylib\)' -o)	
	change_id_name @executable_path/../Frameworks/$LIB $i
done

install_name_tool -id @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_dot_layout.6.dylib
install_name_tool -id @executable_path/../Frameworks/graphviz/libgvplugin_pango.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_pango.6.dylib

cd ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks

for i in *.1.dylib; do
   for j in *.1.dylib; do
       change_install_name $i @executable_path/../Frameworks/$i "${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/$j"
   done
   change_install_name $i @executable_path/../Frameworks/$i "${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca"
done

change_install_name @loader_path/libbass.dylib  @executable_path/../Frameworks/libbass.dylib "${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca"
change_install_name @loader_path/libbass.dylib  @executable_path/../Frameworks/libbass.dylib "${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libAudio.1.dylib"

cd -

sh ${PACCA_GIT}/deploy_tools/osx_qt.sh ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca
sh ${PACCA_GIT}/deploy_tools/osx_qt.sh ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca

# libvlc
change_install_name /opt/local/lib/libvlc.5.dylib @executable_path/../Frameworks/libvlc.5.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca
change_install_name /opt/local/lib/libvlc.5.dylib @executable_path/../Frameworks/libvlc.5.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libVideo.1.dylib
change_install_name /opt/local/lib/libvlc.5.dylib @executable_path/../Frameworks/libvlc.5.dylib  ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib

# libvlccore
change_install_name /opt/local/lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt.dylib
change_install_name /opt/local/lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlccore.7.dylib
change_install_name /opt/local/lib/libvlccore.7.dylib @executable_path/../Frameworks/libvlccore.7.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc.5.dylib

# libvlc-qt.dylib
version_libvlc="1.0.1"

change_install_name @rpath/VLCQtCore.framework/Versions/${version_libvlc}/VLCQtCore @executable_path/../Frameworks/libvlc-qt.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca
change_install_name @rpath/VLCQtCore.framework/Versions/${version_libvlc}/VLCQtCore @executable_path/../Frameworks/libvlc-qt.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libvlc-qt-widgets.dylib
change_install_name @rpath/VLCQtCore.framework/Versions/${version_libvlc}/VLCQtCore @executable_path/../Frameworks/libvlc-qt.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libVideo.1.dylib

# libvlc-qt-widgets
change_install_name @rpath/VLCQtWidgets.framework/Versions/${version_libvlc}/VLCQtWidgets @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/MacOS/Pacca
change_install_name @rpath/VLCQtWidgets.framework/Versions/${version_libvlc}/VLCQtWidgets @executable_path/../Frameworks/libvlc-qt-widgets.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/libVideo.1.dylib

# graphviz
change_install_name /opt/local/lib/graphviz/libgvplugin_dot_layout.6.dylib @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_dot_layout.6.dylib
change_install_name /opt/local/lib/graphviz/libgvplugin_pango.6.dylib @executable_path/../Frameworks/graphviz/libgvplugin_dot_layout.6.dylib ${LOCAL_PATH_}/${APP_NAME}/Contents/Frameworks/graphviz/libgvplugin_pango.6.dylib

# deploy plugins - executar na primeira vez em que for trabalhar
#deploy_plugins

# deploy to final version - apenas para versão completa do deploy
#macdeployqt ${LOCAL_PATH_}/${APP_NAME}

echo sucess
