# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thongpv3/CLionProjects/CBORBenchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thongpv3/CLionProjects/CBORBenchmark/build

# Include any dependencies generated for this target.
include include/libcbor/examples/CMakeFiles/readfile.dir/depend.make

# Include the progress variables for this target.
include include/libcbor/examples/CMakeFiles/readfile.dir/progress.make

# Include the compile flags for this target's objects.
include include/libcbor/examples/CMakeFiles/readfile.dir/flags.make

include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o: include/libcbor/examples/CMakeFiles/readfile.dir/flags.make
include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o: ../include/libcbor/examples/readfile.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thongpv3/CLionProjects/CBORBenchmark/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o"
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/readfile.dir/readfile.c.o   -c /home/thongpv3/CLionProjects/CBORBenchmark/include/libcbor/examples/readfile.c

include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/readfile.dir/readfile.c.i"
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/thongpv3/CLionProjects/CBORBenchmark/include/libcbor/examples/readfile.c > CMakeFiles/readfile.dir/readfile.c.i

include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/readfile.dir/readfile.c.s"
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/thongpv3/CLionProjects/CBORBenchmark/include/libcbor/examples/readfile.c -o CMakeFiles/readfile.dir/readfile.c.s

include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.requires:

.PHONY : include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.requires

include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.provides: include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.requires
	$(MAKE) -f include/libcbor/examples/CMakeFiles/readfile.dir/build.make include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.provides.build
.PHONY : include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.provides

include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.provides.build: include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o


# Object files for target readfile
readfile_OBJECTS = \
"CMakeFiles/readfile.dir/readfile.c.o"

# External object files for target readfile
readfile_EXTERNAL_OBJECTS =

include/libcbor/examples/readfile: include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o
include/libcbor/examples/readfile: include/libcbor/examples/CMakeFiles/readfile.dir/build.make
include/libcbor/examples/readfile: include/libcbor/src/libcbor.a
include/libcbor/examples/readfile: include/libcbor/examples/CMakeFiles/readfile.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thongpv3/CLionProjects/CBORBenchmark/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable readfile"
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readfile.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/libcbor/examples/CMakeFiles/readfile.dir/build: include/libcbor/examples/readfile

.PHONY : include/libcbor/examples/CMakeFiles/readfile.dir/build

include/libcbor/examples/CMakeFiles/readfile.dir/requires: include/libcbor/examples/CMakeFiles/readfile.dir/readfile.c.o.requires

.PHONY : include/libcbor/examples/CMakeFiles/readfile.dir/requires

include/libcbor/examples/CMakeFiles/readfile.dir/clean:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/examples && $(CMAKE_COMMAND) -P CMakeFiles/readfile.dir/cmake_clean.cmake
.PHONY : include/libcbor/examples/CMakeFiles/readfile.dir/clean

include/libcbor/examples/CMakeFiles/readfile.dir/depend:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thongpv3/CLionProjects/CBORBenchmark /home/thongpv3/CLionProjects/CBORBenchmark/include/libcbor/examples /home/thongpv3/CLionProjects/CBORBenchmark/build /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/examples /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/examples/CMakeFiles/readfile.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/libcbor/examples/CMakeFiles/readfile.dir/depend

