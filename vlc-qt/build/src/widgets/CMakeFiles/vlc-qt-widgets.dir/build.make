# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build

# Include any dependencies generated for this target.
include src/widgets/CMakeFiles/vlc-qt-widgets.dir/depend.make

# Include the progress variables for this target.
include src/widgets/CMakeFiles/vlc-qt-widgets.dir/progress.make

# Include the compile flags for this target's objects.
include src/widgets/CMakeFiles/vlc-qt-widgets.dir/flags.make

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o: src/widgets/CMakeFiles/vlc-qt-widgets.dir/flags.make
src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o: ../src/widgets/ControlAudio.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o -c /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/ControlAudio.cpp

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.i"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/ControlAudio.cpp > CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.i

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.s"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/ControlAudio.cpp -o CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.s

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.requires:
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.requires

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.provides: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.requires
	$(MAKE) -f src/widgets/CMakeFiles/vlc-qt-widgets.dir/build.make src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.provides.build
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.provides

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.provides.build: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o: src/widgets/CMakeFiles/vlc-qt-widgets.dir/flags.make
src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o: ../src/widgets/ControlVideo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o -c /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/ControlVideo.cpp

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.i"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/ControlVideo.cpp > CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.i

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.s"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/ControlVideo.cpp -o CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.s

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.requires:
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.requires

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.provides: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.requires
	$(MAKE) -f src/widgets/CMakeFiles/vlc-qt-widgets.dir/build.make src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.provides.build
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.provides

src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.provides.build: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o: src/widgets/CMakeFiles/vlc-qt-widgets.dir/flags.make
src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o: ../src/widgets/WidgetSeek.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o -c /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetSeek.cpp

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.i"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetSeek.cpp > CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.i

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.s"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetSeek.cpp -o CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.s

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.requires:
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.requires

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.provides: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.requires
	$(MAKE) -f src/widgets/CMakeFiles/vlc-qt-widgets.dir/build.make src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.provides.build
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.provides

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.provides.build: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o: src/widgets/CMakeFiles/vlc-qt-widgets.dir/flags.make
src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o: ../src/widgets/WidgetVideo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o -c /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetVideo.cpp

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.i"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetVideo.cpp > CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.i

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.s"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetVideo.cpp -o CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.s

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.requires:
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.requires

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.provides: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.requires
	$(MAKE) -f src/widgets/CMakeFiles/vlc-qt-widgets.dir/build.make src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.provides.build
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.provides

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.provides.build: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o: src/widgets/CMakeFiles/vlc-qt-widgets.dir/flags.make
src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o: ../src/widgets/WidgetVolumeSlider.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o -c /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetVolumeSlider.cpp

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.i"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetVolumeSlider.cpp > CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.i

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.s"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets/WidgetVolumeSlider.cpp -o CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.s

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.requires:
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.requires

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.provides: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.requires
	$(MAKE) -f src/widgets/CMakeFiles/vlc-qt-widgets.dir/build.make src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.provides.build
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.provides

src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.provides.build: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o

src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o: src/widgets/CMakeFiles/vlc-qt-widgets.dir/flags.make
src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o: src/widgets/vlc-qt-widgets_automoc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o -c /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/vlc-qt-widgets_automoc.cpp

src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.i"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/vlc-qt-widgets_automoc.cpp > CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.i

src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.s"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/vlc-qt-widgets_automoc.cpp -o CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.s

src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.requires:
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.requires

src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.provides: src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.requires
	$(MAKE) -f src/widgets/CMakeFiles/vlc-qt-widgets.dir/build.make src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.provides.build
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.provides

src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.provides.build: src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o

# Object files for target vlc-qt-widgets
vlc__qt__widgets_OBJECTS = \
"CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o" \
"CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o" \
"CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o" \
"CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o" \
"CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o" \
"CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o"

# External object files for target vlc-qt-widgets
vlc__qt__widgets_EXTERNAL_OBJECTS =

src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o
src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o
src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o
src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o
src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o
src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o
src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/build.make
src/widgets/libvlc-qt-widgets.dylib: src/core/libvlc-qt.dylib
src/widgets/libvlc-qt-widgets.dylib: /Users/alexsantana/Qt5.3.2/5.3/clang_64/lib/QtWidgets.framework/QtWidgets
src/widgets/libvlc-qt-widgets.dylib: /Users/alexsantana/Qt5.3.2/5.3/clang_64/lib/QtGui.framework/QtGui
src/widgets/libvlc-qt-widgets.dylib: /Users/alexsantana/Qt5.3.2/5.3/clang_64/lib/QtCore.framework/QtCore
src/widgets/libvlc-qt-widgets.dylib: src/widgets/CMakeFiles/vlc-qt-widgets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libvlc-qt-widgets.dylib"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vlc-qt-widgets.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/install_name_tool -change /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/core/libvlc-qt.dylib @loader_path/../lib/libvlc-qt.dylib /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/libvlc-qt-widgets.dylib
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/install_name_tool -change @loader_path/lib/libvlc.5.dylib @loader_path/../lib/libvlc.5.dylib /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/libvlc-qt-widgets.dylib
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/install_name_tool -change @loader_path/lib/libvlccore.5.dylib @loader_path/../lib/libvlccore.5.dylib /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/libvlc-qt-widgets.dylib
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && /usr/bin/install_name_tool -change @loader_path/lib/libvlccore.7.dylib @loader_path/../lib/libvlccore.7.dylib /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/libvlc-qt-widgets.dylib

# Rule to build all files generated by this target.
src/widgets/CMakeFiles/vlc-qt-widgets.dir/build: src/widgets/libvlc-qt-widgets.dylib
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/build

src/widgets/CMakeFiles/vlc-qt-widgets.dir/requires: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlAudio.cpp.o.requires
src/widgets/CMakeFiles/vlc-qt-widgets.dir/requires: src/widgets/CMakeFiles/vlc-qt-widgets.dir/ControlVideo.cpp.o.requires
src/widgets/CMakeFiles/vlc-qt-widgets.dir/requires: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetSeek.cpp.o.requires
src/widgets/CMakeFiles/vlc-qt-widgets.dir/requires: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVideo.cpp.o.requires
src/widgets/CMakeFiles/vlc-qt-widgets.dir/requires: src/widgets/CMakeFiles/vlc-qt-widgets.dir/WidgetVolumeSlider.cpp.o.requires
src/widgets/CMakeFiles/vlc-qt-widgets.dir/requires: src/widgets/CMakeFiles/vlc-qt-widgets.dir/vlc-qt-widgets_automoc.cpp.o.requires
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/requires

src/widgets/CMakeFiles/vlc-qt-widgets.dir/clean:
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets && $(CMAKE_COMMAND) -P CMakeFiles/vlc-qt-widgets.dir/cmake_clean.cmake
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/clean

src/widgets/CMakeFiles/vlc-qt-widgets.dir/depend:
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/widgets /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/widgets/CMakeFiles/vlc-qt-widgets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/widgets/CMakeFiles/vlc-qt-widgets.dir/depend
