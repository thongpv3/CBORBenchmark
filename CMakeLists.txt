cmake_minimum_required(VERSION 3.7)
project(CBORBenchmark)

set(CMAKE_CXX_STANDARD 14)

set(BUILD_SHARED_LIBS OFF)
# Configure FindBoost module to locate static libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")



add_subdirectory(include)
add_subdirectory(serializer)
add_subdirectory(benchmarks)
