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

# Utility rule file for coverage.

# Include the progress variables for this target.
include include/libcbor/CMakeFiles/coverage.dir/progress.make

include/libcbor/CMakeFiles/coverage:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor && ctest
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor && lcov --capture --directory . --output-file coverage.info
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor && genhtml coverage.info --highlight --legend --output-directory coverage_html
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor && echo Coverage\ report\ ready:\ file:///home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/coverage_html/index.html

coverage: include/libcbor/CMakeFiles/coverage
coverage: include/libcbor/CMakeFiles/coverage.dir/build.make

.PHONY : coverage

# Rule to build all files generated by this target.
include/libcbor/CMakeFiles/coverage.dir/build: coverage

.PHONY : include/libcbor/CMakeFiles/coverage.dir/build

include/libcbor/CMakeFiles/coverage.dir/clean:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor && $(CMAKE_COMMAND) -P CMakeFiles/coverage.dir/cmake_clean.cmake
.PHONY : include/libcbor/CMakeFiles/coverage.dir/clean

include/libcbor/CMakeFiles/coverage.dir/depend:
	cd /home/thongpv3/CLionProjects/CBORBenchmark/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thongpv3/CLionProjects/CBORBenchmark /home/thongpv3/CLionProjects/CBORBenchmark/include/libcbor /home/thongpv3/CLionProjects/CBORBenchmark/build /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor /home/thongpv3/CLionProjects/CBORBenchmark/build/include/libcbor/CMakeFiles/coverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/libcbor/CMakeFiles/coverage.dir/depend

