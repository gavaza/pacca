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

# Utility rule file for vlc-qt_automoc.

# Include the progress variables for this target.
include src/core/CMakeFiles/vlc-qt_automoc.dir/progress.make

src/core/CMakeFiles/vlc-qt_automoc:
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Automatic moc, uic and rcc for target vlc-qt"
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/core && /opt/local/bin/cmake -E cmake_autogen /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/core/CMakeFiles/vlc-qt_automoc.dir/ ""

vlc-qt_automoc: src/core/CMakeFiles/vlc-qt_automoc
vlc-qt_automoc: src/core/CMakeFiles/vlc-qt_automoc.dir/build.make
.PHONY : vlc-qt_automoc

# Rule to build all files generated by this target.
src/core/CMakeFiles/vlc-qt_automoc.dir/build: vlc-qt_automoc
.PHONY : src/core/CMakeFiles/vlc-qt_automoc.dir/build

src/core/CMakeFiles/vlc-qt_automoc.dir/clean:
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/core && $(CMAKE_COMMAND) -P CMakeFiles/vlc-qt_automoc.dir/cmake_clean.cmake
.PHONY : src/core/CMakeFiles/vlc-qt_automoc.dir/clean

src/core/CMakeFiles/vlc-qt_automoc.dir/depend:
	cd /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/src/core /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/core /Users/alexsantana/Projetos/Pacca2/code/trunk/vlc-qt/build/src/core/CMakeFiles/vlc-qt_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/core/CMakeFiles/vlc-qt_automoc.dir/depend

