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
CMAKE_COMMAND = /opt/clion-2017.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2017.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thongpv3/CLionProjects/CBORBenchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thongpv3/CLionProjects/CBORBenchmark/cmake-build-debug

# Utility rule file for ExperimentalSubmit.

# Include the progress variables for this target.
include include/libcbor/CMakeFiles/ExperimentalSubmit.dir/progress.make

include/libcbor/CMakeFiles/ExperimentalSubmit:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/cmake-build-debug/include/libcbor && /opt/clion-2017.1/bin/cmake/bin/ctest -D ExperimentalSubmit

ExperimentalSubmit: include/libcbor/CMakeFiles/ExperimentalSubmit
ExperimentalSubmit: include/libcbor/CMakeFiles/ExperimentalSubmit.dir/build.make

.PHONY : ExperimentalSubmit

# Rule to build all files generated by this target.
include/libcbor/CMakeFiles/ExperimentalSubmit.dir/build: ExperimentalSubmit

.PHONY : include/libcbor/CMakeFiles/ExperimentalSubmit.dir/build

include/libcbor/CMakeFiles/ExperimentalSubmit.dir/clean:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/cmake-build-debug/include/libcbor && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalSubmit.dir/cmake_clean.cmake
.PHONY : include/libcbor/CMakeFiles/ExperimentalSubmit.dir/clean

include/libcbor/CMakeFiles/ExperimentalSubmit.dir/depend:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thongpv3/CLionProjects/CBORBenchmark /home/thongpv3/CLionProjects/CBORBenchmark/include/libcbor /home/thongpv3/CLionProjects/CBORBenchmark/cmake-build-debug /home/thongpv3/CLionProjects/CBORBenchmark/cmake-build-debug/include/libcbor /home/thongpv3/CLionProjects/CBORBenchmark/cmake-build-debug/include/libcbor/CMakeFiles/ExperimentalSubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/libcbor/CMakeFiles/ExperimentalSubmit.dir/depend

