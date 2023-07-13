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
include src/CMakeFiles/freenect.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/freenect.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/freenect.dir/flags.make

src/CMakeFiles/freenect.dir/core.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/core.c.o: ../src/core.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/freenect.dir/core.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/core.c.o   -c /home/forklift2023/libfreenect/src/core.c

src/CMakeFiles/freenect.dir/core.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/core.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/core.c > CMakeFiles/freenect.dir/core.c.i

src/CMakeFiles/freenect.dir/core.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/core.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/core.c -o CMakeFiles/freenect.dir/core.c.s

src/CMakeFiles/freenect.dir/core.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/core.c.o.requires

src/CMakeFiles/freenect.dir/core.c.o.provides: src/CMakeFiles/freenect.dir/core.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/core.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/core.c.o.provides

src/CMakeFiles/freenect.dir/core.c.o.provides.build: src/CMakeFiles/freenect.dir/core.c.o


src/CMakeFiles/freenect.dir/tilt.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/tilt.c.o: ../src/tilt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/freenect.dir/tilt.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/tilt.c.o   -c /home/forklift2023/libfreenect/src/tilt.c

src/CMakeFiles/freenect.dir/tilt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/tilt.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/tilt.c > CMakeFiles/freenect.dir/tilt.c.i

src/CMakeFiles/freenect.dir/tilt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/tilt.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/tilt.c -o CMakeFiles/freenect.dir/tilt.c.s

src/CMakeFiles/freenect.dir/tilt.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/tilt.c.o.requires

src/CMakeFiles/freenect.dir/tilt.c.o.provides: src/CMakeFiles/freenect.dir/tilt.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/tilt.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/tilt.c.o.provides

src/CMakeFiles/freenect.dir/tilt.c.o.provides.build: src/CMakeFiles/freenect.dir/tilt.c.o


src/CMakeFiles/freenect.dir/cameras.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/cameras.c.o: ../src/cameras.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/freenect.dir/cameras.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/cameras.c.o   -c /home/forklift2023/libfreenect/src/cameras.c

src/CMakeFiles/freenect.dir/cameras.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/cameras.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/cameras.c > CMakeFiles/freenect.dir/cameras.c.i

src/CMakeFiles/freenect.dir/cameras.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/cameras.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/cameras.c -o CMakeFiles/freenect.dir/cameras.c.s

src/CMakeFiles/freenect.dir/cameras.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/cameras.c.o.requires

src/CMakeFiles/freenect.dir/cameras.c.o.provides: src/CMakeFiles/freenect.dir/cameras.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/cameras.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/cameras.c.o.provides

src/CMakeFiles/freenect.dir/cameras.c.o.provides.build: src/CMakeFiles/freenect.dir/cameras.c.o


src/CMakeFiles/freenect.dir/flags.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/flags.c.o: ../src/flags.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/freenect.dir/flags.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/flags.c.o   -c /home/forklift2023/libfreenect/src/flags.c

src/CMakeFiles/freenect.dir/flags.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/flags.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/flags.c > CMakeFiles/freenect.dir/flags.c.i

src/CMakeFiles/freenect.dir/flags.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/flags.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/flags.c -o CMakeFiles/freenect.dir/flags.c.s

src/CMakeFiles/freenect.dir/flags.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/flags.c.o.requires

src/CMakeFiles/freenect.dir/flags.c.o.provides: src/CMakeFiles/freenect.dir/flags.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/flags.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/flags.c.o.provides

src/CMakeFiles/freenect.dir/flags.c.o.provides.build: src/CMakeFiles/freenect.dir/flags.c.o


src/CMakeFiles/freenect.dir/usb_libusb10.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/usb_libusb10.c.o: ../src/usb_libusb10.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/freenect.dir/usb_libusb10.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/usb_libusb10.c.o   -c /home/forklift2023/libfreenect/src/usb_libusb10.c

src/CMakeFiles/freenect.dir/usb_libusb10.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/usb_libusb10.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/usb_libusb10.c > CMakeFiles/freenect.dir/usb_libusb10.c.i

src/CMakeFiles/freenect.dir/usb_libusb10.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/usb_libusb10.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/usb_libusb10.c -o CMakeFiles/freenect.dir/usb_libusb10.c.s

src/CMakeFiles/freenect.dir/usb_libusb10.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/usb_libusb10.c.o.requires

src/CMakeFiles/freenect.dir/usb_libusb10.c.o.provides: src/CMakeFiles/freenect.dir/usb_libusb10.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/usb_libusb10.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/usb_libusb10.c.o.provides

src/CMakeFiles/freenect.dir/usb_libusb10.c.o.provides.build: src/CMakeFiles/freenect.dir/usb_libusb10.c.o


src/CMakeFiles/freenect.dir/registration.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/registration.c.o: ../src/registration.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/freenect.dir/registration.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/registration.c.o   -c /home/forklift2023/libfreenect/src/registration.c

src/CMakeFiles/freenect.dir/registration.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/registration.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/registration.c > CMakeFiles/freenect.dir/registration.c.i

src/CMakeFiles/freenect.dir/registration.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/registration.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/registration.c -o CMakeFiles/freenect.dir/registration.c.s

src/CMakeFiles/freenect.dir/registration.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/registration.c.o.requires

src/CMakeFiles/freenect.dir/registration.c.o.provides: src/CMakeFiles/freenect.dir/registration.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/registration.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/registration.c.o.provides

src/CMakeFiles/freenect.dir/registration.c.o.provides.build: src/CMakeFiles/freenect.dir/registration.c.o


src/CMakeFiles/freenect.dir/audio.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/audio.c.o: ../src/audio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/CMakeFiles/freenect.dir/audio.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/audio.c.o   -c /home/forklift2023/libfreenect/src/audio.c

src/CMakeFiles/freenect.dir/audio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/audio.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/audio.c > CMakeFiles/freenect.dir/audio.c.i

src/CMakeFiles/freenect.dir/audio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/audio.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/audio.c -o CMakeFiles/freenect.dir/audio.c.s

src/CMakeFiles/freenect.dir/audio.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/audio.c.o.requires

src/CMakeFiles/freenect.dir/audio.c.o.provides: src/CMakeFiles/freenect.dir/audio.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/audio.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/audio.c.o.provides

src/CMakeFiles/freenect.dir/audio.c.o.provides.build: src/CMakeFiles/freenect.dir/audio.c.o


src/CMakeFiles/freenect.dir/loader.c.o: src/CMakeFiles/freenect.dir/flags.make
src/CMakeFiles/freenect.dir/loader.c.o: ../src/loader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/CMakeFiles/freenect.dir/loader.c.o"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect.dir/loader.c.o   -c /home/forklift2023/libfreenect/src/loader.c

src/CMakeFiles/freenect.dir/loader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect.dir/loader.c.i"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forklift2023/libfreenect/src/loader.c > CMakeFiles/freenect.dir/loader.c.i

src/CMakeFiles/freenect.dir/loader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect.dir/loader.c.s"
	cd /home/forklift2023/libfreenect/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forklift2023/libfreenect/src/loader.c -o CMakeFiles/freenect.dir/loader.c.s

src/CMakeFiles/freenect.dir/loader.c.o.requires:

.PHONY : src/CMakeFiles/freenect.dir/loader.c.o.requires

src/CMakeFiles/freenect.dir/loader.c.o.provides: src/CMakeFiles/freenect.dir/loader.c.o.requires
	$(MAKE) -f src/CMakeFiles/freenect.dir/build.make src/CMakeFiles/freenect.dir/loader.c.o.provides.build
.PHONY : src/CMakeFiles/freenect.dir/loader.c.o.provides

src/CMakeFiles/freenect.dir/loader.c.o.provides.build: src/CMakeFiles/freenect.dir/loader.c.o


# Object files for target freenect
freenect_OBJECTS = \
"CMakeFiles/freenect.dir/core.c.o" \
"CMakeFiles/freenect.dir/tilt.c.o" \
"CMakeFiles/freenect.dir/cameras.c.o" \
"CMakeFiles/freenect.dir/flags.c.o" \
"CMakeFiles/freenect.dir/usb_libusb10.c.o" \
"CMakeFiles/freenect.dir/registration.c.o" \
"CMakeFiles/freenect.dir/audio.c.o" \
"CMakeFiles/freenect.dir/loader.c.o"

# External object files for target freenect
freenect_EXTERNAL_OBJECTS =

lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/core.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/tilt.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/cameras.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/flags.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/usb_libusb10.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/registration.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/audio.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/loader.c.o
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/build.make
lib/libfreenect.so.0.7.0: /usr/lib/aarch64-linux-gnu/libusb-1.0.so
lib/libfreenect.so.0.7.0: src/CMakeFiles/freenect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/forklift2023/libfreenect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C shared library ../lib/libfreenect.so"
	cd /home/forklift2023/libfreenect/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect.dir/link.txt --verbose=$(VERBOSE)
	cd /home/forklift2023/libfreenect/build/src && $(CMAKE_COMMAND) -E cmake_symlink_library ../lib/libfreenect.so.0.7.0 ../lib/libfreenect.so.0 ../lib/libfreenect.so

lib/libfreenect.so.0: lib/libfreenect.so.0.7.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libfreenect.so.0

lib/libfreenect.so: lib/libfreenect.so.0.7.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libfreenect.so

# Rule to build all files generated by this target.
src/CMakeFiles/freenect.dir/build: lib/libfreenect.so

.PHONY : src/CMakeFiles/freenect.dir/build

src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/core.c.o.requires
src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/tilt.c.o.requires
src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/cameras.c.o.requires
src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/flags.c.o.requires
src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/usb_libusb10.c.o.requires
src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/registration.c.o.requires
src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/audio.c.o.requires
src/CMakeFiles/freenect.dir/requires: src/CMakeFiles/freenect.dir/loader.c.o.requires

.PHONY : src/CMakeFiles/freenect.dir/requires

src/CMakeFiles/freenect.dir/clean:
	cd /home/forklift2023/libfreenect/build/src && $(CMAKE_COMMAND) -P CMakeFiles/freenect.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/freenect.dir/clean

src/CMakeFiles/freenect.dir/depend:
	cd /home/forklift2023/libfreenect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/forklift2023/libfreenect /home/forklift2023/libfreenect/src /home/forklift2023/libfreenect/build /home/forklift2023/libfreenect/build/src /home/forklift2023/libfreenect/build/src/CMakeFiles/freenect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/freenect.dir/depend

