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

# Utility rule file for ContinuousBuild.

# Include the progress variables for this target.
include include/libcbor/CMakeFiles/ContinuousBuild.dir/progress.make

include/libcbor/CMakeFiles/ContinuousBuild:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor && /usr/local/bin/ctest -D ContinuousBuild

ContinuousBuild: include/libcbor/CMakeFiles/ContinuousBuild
ContinuousBuild: include/libcbor/CMakeFiles/ContinuousBuild.dir/build.make

.PHONY : ContinuousBuild

# Rule to build all files generated by this target.
include/libcbor/CMakeFiles/ContinuousBuild.dir/build: ContinuousBuild

.PHONY : include/libcbor/CMakeFiles/ContinuousBuild.dir/build

include/libcbor/CMakeFiles/ContinuousBuild.dir/clean:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousBuild.dir/cmake_clean.cmake
.PHONY : include/libcbor/CMakeFiles/ContinuousBuild.dir/clean

include/libcbor/CMakeFiles/ContinuousBuild.dir/depend:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thongpv3/CLionProjects/CBORBenchmark /home/thongpv3/CLionProjects/CBORBenchmark/include/libcbor /home/thongpv3/CLionProjects/CBORBenchmark/build /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/CMakeFiles/ContinuousBuild.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/libcbor/CMakeFiles/ContinuousBuild.dir/depend
