# Install script for directory: /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/qml

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/osx")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/qml/libvlc-qt-qml.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvlc-qt-qml.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvlc-qt-qml.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvlc-qt-qml.dylib")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/osx/include/vlc-qt/QmlVideoObject.h;/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/osx/include/vlc-qt/QmlVideoPlayer.h;/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/osx/include/vlc-qt/SharedExportQml.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/osx/include/vlc-qt" TYPE FILE FILES
    "/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/qml/QmlVideoObject.h"
    "/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/qml/QmlVideoPlayer.h"
    "/Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/qml/SharedExportQml.h"
    )
endif()

