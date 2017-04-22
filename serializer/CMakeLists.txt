set(CBOR_SERIALIZER_HEADERS
        cbor_item.h
        libcbor_serializer.h
        serializer.h
        main.cpp)
add_library(cbor_serializer INTERFACE)
target_include_directories(cbor_serializer INTERFACE cbor)
target_link_libraries(cbor_serializer INTERFACE cbor)

#todo remove this, just for clion reconigze header file
add_executable(dummy ${CBOR_SERIALIZER_HEADERS})