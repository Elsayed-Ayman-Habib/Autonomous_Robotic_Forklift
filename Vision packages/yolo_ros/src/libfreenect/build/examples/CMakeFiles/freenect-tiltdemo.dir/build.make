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
CMAKE_SOURCE_DIR = /home/forklift2023/libfreenect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/forklift2023/libfreenect/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/freenect-tiltdemo.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/freenect-tiltdemo.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/freenect-tiltdemo.dir/flags.make

examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o: examples/CMakeFiles/freenect-tiltdemo.dir/flags.make
examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o: ../examples/tiltdemo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o"
	cd /home/forklift2023/libfreenect/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o   -c /home/forklift2023/libfreenect/examples/tiltdemo.c

examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.i"
	cd /home/forklift2023/libfreenect/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/examples/tiltdemo.c > CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.i

examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.s"
	cd /home/forklift2023/libfreenect/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/examples/tiltdemo.c -o CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.s

examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.requires:

.PHONY : examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.requires

examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.provides: examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.requires
	$(MAKE) -f examples/CMakeFiles/freenect-tiltdemo.dir/build.make examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.provides.build
.PHONY : examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.provides

examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.provides.build: examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o


# Object files for target freenect-tiltdemo
freenect__tiltdemo_OBJECTS = \
"CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o"

# External object files for target freenect-tiltdemo
freenect__tiltdemo_EXTERNAL_OBJECTS =

bin/freenect-tiltdemo: examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o
bin/freenect-tiltdemo: examples/CMakeFiles/freenect-tiltdemo.dir/build.make
bin/freenect-tiltdemo: lib/libfreenect_sync.so.0.7.0
bin/freenect-tiltdemo: lib/libfreenect.so.0.7.0
bin/freenect-tiltdemo: /usr/lib/aarch64-linux-gnu/libusb-1.0.so
bin/freenect-tiltdemo: examples/CMakeFiles/freenect-tiltdemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/freenect-tiltdemo"
	cd /home/forklift2023/libfreenect/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect-tiltdemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/freenect-tiltdemo.dir/build: bin/freenect-tiltdemo

.PHONY : examples/CMakeFiles/freenect-tiltdemo.dir/build

examples/CMakeFiles/freenect-tiltdemo.dir/requires: examples/CMakeFiles/freenect-tiltdemo.dir/tiltdemo.c.o.requires

.PHONY : examples/CMakeFiles/freenect-tiltdemo.dir/requires

examples/CMakeFiles/freenect-tiltdemo.dir/clean:
	cd /home/forklift2023/libfreenect/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/freenect-tiltdemo.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/freenect-tiltdemo.dir/clean

examples/CMakeFiles/freenect-tiltdemo.dir/depend:
	cd /home/forklift2023/libfreenect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/forklift2023/libfreenect /home/forklift2023/libfreenect/examples /home/forklift2023/libfreenect/build /home/forklift2023/libfreenect/build/examples /home/forklift2023/libfreenect/build/examples/CMakeFiles/freenect-tiltdemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/freenect-tiltdemo.dir/depend

