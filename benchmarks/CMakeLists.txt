add_executable(TestLibCBOR libcbor/test_libcbor.cpp)
target_link_libraries(TestLibCBOR PRIVATE cbor cbor_serializer)

add_executable(TestTinyCBOR libcbor/test_tinycbor.cpp)
target_link_libraries(TestTinyCBOR PRIVATE tinycbor cbor_serializer)
