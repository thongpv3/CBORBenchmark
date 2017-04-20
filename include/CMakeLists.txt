#Not benchmark because it only support convert data from json to cbor and vice versa
#add_subdirectory(json)
#add_library(json ALIAS nlohmann_json)

add_subdirectory(libcbor)
target_include_directories(cbor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libcbor/src ${CMAKE_CURRENT_BINARY_DIR}/libcbor)


add_subdirectory(tinycbor)
add_subdirectory(nonius)