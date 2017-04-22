# execute_process(COMMAND make) #FIXME: Do this only on the first time


find_package(PkgConfig REQUIRED)
execute_process(COMMAND pkg-config --cflags --libs ${CMAKE_CURRENT_SOURCE_DIR}/tinycbor.pc OUTPUT_VARIABLE TINYCBOR_LIB)
string(STRIP "${TINYCBOR_LIB}" TINYCBOR_LIB)
message(STATUS "AAA ${TINYCBOR_LIB} BBB")
add_library(tinycbor INTERFACE)
target_link_libraries(tinycbor INTERFACE ${TINYCBOR_LIB})
target_include_directories(tinycbor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
