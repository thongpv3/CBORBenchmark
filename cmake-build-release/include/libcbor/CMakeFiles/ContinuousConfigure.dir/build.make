# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /opt/clion-2017.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2017.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thongpv87/CLionProjects/CBORBenchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thongpv87/CLionProjects/CBORBenchmark/cmake-build-release

# Utility rule file for ContinuousConfigure.

# Include the progress variables for this target.
include include/libcbor/CMakeFiles/ContinuousConfigure.dir/progress.make

include/libcbor/CMakeFiles/ContinuousConfigure:
	cd /home/thongpv87/CLionProjects/CBORBenchmark/cmake-build-release/include/libcbor && /opt/clion-2017.1.1/bin/cmake/bin/ctest -D ContinuousConfigure

ContinuousConfigure: include/libcbor/CMakeFiles/ContinuousConfigure
ContinuousConfigure: include/libcbor/CMakeFiles/ContinuousConfigure.dir/build.make

.PHONY : ContinuousConfigure

# Rule to build all files generated by this target.
include/libcbor/CMakeFiles/ContinuousConfigure.dir/build: ContinuousConfigure

.PHONY : include/libcbor/CMakeFiles/ContinuousConfigure.dir/build

include/libcbor/CMakeFiles/ContinuousConfigure.dir/clean:
	cd /home/thongpv87/CLionProjects/CBORBenchmark/cmake-build-release/include/libcbor && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousConfigure.dir/cmake_clean.cmake
.PHONY : include/libcbor/CMakeFiles/ContinuousConfigure.dir/clean

include/libcbor/CMakeFiles/ContinuousConfigure.dir/depend:
	cd /home/thongpv87/CLionProjects/CBORBenchmark/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thongpv87/CLionProjects/CBORBenchmark /home/thongpv87/CLionProjects/CBORBenchmark/include/libcbor /home/thongpv87/CLionProjects/CBORBenchmark/cmake-build-release /home/thongpv87/CLionProjects/CBORBenchmark/cmake-build-release/include/libcbor /home/thongpv87/CLionProjects/CBORBenchmark/cmake-build-release/include/libcbor/CMakeFiles/ContinuousConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/libcbor/CMakeFiles/ContinuousConfigure.dir/depend
