# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/formulos/Documents/github/supercomp2.0/projeto-03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/formulos/Documents/github/supercomp2.0/projeto-03

# Include any dependencies generated for this target.
include CMakeFiles/seq.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/seq.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/seq.dir/flags.make

CMakeFiles/seq.dir/tsp.cc.o: CMakeFiles/seq.dir/flags.make
CMakeFiles/seq.dir/tsp.cc.o: tsp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/formulos/Documents/github/supercomp2.0/projeto-03/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/seq.dir/tsp.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/seq.dir/tsp.cc.o -c /home/formulos/Documents/github/supercomp2.0/projeto-03/tsp.cc

CMakeFiles/seq.dir/tsp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/seq.dir/tsp.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/formulos/Documents/github/supercomp2.0/projeto-03/tsp.cc > CMakeFiles/seq.dir/tsp.cc.i

CMakeFiles/seq.dir/tsp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/seq.dir/tsp.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/formulos/Documents/github/supercomp2.0/projeto-03/tsp.cc -o CMakeFiles/seq.dir/tsp.cc.s

CMakeFiles/seq.dir/tsp.cc.o.requires:

.PHONY : CMakeFiles/seq.dir/tsp.cc.o.requires

CMakeFiles/seq.dir/tsp.cc.o.provides: CMakeFiles/seq.dir/tsp.cc.o.requires
	$(MAKE) -f CMakeFiles/seq.dir/build.make CMakeFiles/seq.dir/tsp.cc.o.provides.build
.PHONY : CMakeFiles/seq.dir/tsp.cc.o.provides

CMakeFiles/seq.dir/tsp.cc.o.provides.build: CMakeFiles/seq.dir/tsp.cc.o


CMakeFiles/seq.dir/place.cpp.o: CMakeFiles/seq.dir/flags.make
CMakeFiles/seq.dir/place.cpp.o: place.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/formulos/Documents/github/supercomp2.0/projeto-03/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/seq.dir/place.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/seq.dir/place.cpp.o -c /home/formulos/Documents/github/supercomp2.0/projeto-03/place.cpp

CMakeFiles/seq.dir/place.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/seq.dir/place.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/formulos/Documents/github/supercomp2.0/projeto-03/place.cpp > CMakeFiles/seq.dir/place.cpp.i

CMakeFiles/seq.dir/place.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/seq.dir/place.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/formulos/Documents/github/supercomp2.0/projeto-03/place.cpp -o CMakeFiles/seq.dir/place.cpp.s

CMakeFiles/seq.dir/place.cpp.o.requires:

.PHONY : CMakeFiles/seq.dir/place.cpp.o.requires

CMakeFiles/seq.dir/place.cpp.o.provides: CMakeFiles/seq.dir/place.cpp.o.requires
	$(MAKE) -f CMakeFiles/seq.dir/build.make CMakeFiles/seq.dir/place.cpp.o.provides.build
.PHONY : CMakeFiles/seq.dir/place.cpp.o.provides

CMakeFiles/seq.dir/place.cpp.o.provides.build: CMakeFiles/seq.dir/place.cpp.o


# Object files for target seq
seq_OBJECTS = \
"CMakeFiles/seq.dir/tsp.cc.o" \
"CMakeFiles/seq.dir/place.cpp.o"

# External object files for target seq
seq_EXTERNAL_OBJECTS =

seq: CMakeFiles/seq.dir/tsp.cc.o
seq: CMakeFiles/seq.dir/place.cpp.o
seq: CMakeFiles/seq.dir/build.make
seq: CMakeFiles/seq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/formulos/Documents/github/supercomp2.0/projeto-03/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable seq"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/seq.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/seq.dir/build: seq

.PHONY : CMakeFiles/seq.dir/build

CMakeFiles/seq.dir/requires: CMakeFiles/seq.dir/tsp.cc.o.requires
CMakeFiles/seq.dir/requires: CMakeFiles/seq.dir/place.cpp.o.requires

.PHONY : CMakeFiles/seq.dir/requires

CMakeFiles/seq.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/seq.dir/cmake_clean.cmake
.PHONY : CMakeFiles/seq.dir/clean

CMakeFiles/seq.dir/depend:
	cd /home/formulos/Documents/github/supercomp2.0/projeto-03 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/formulos/Documents/github/supercomp2.0/projeto-03 /home/formulos/Documents/github/supercomp2.0/projeto-03 /home/formulos/Documents/github/supercomp2.0/projeto-03 /home/formulos/Documents/github/supercomp2.0/projeto-03 /home/formulos/Documents/github/supercomp2.0/projeto-03/CMakeFiles/seq.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/seq.dir/depend

