add_executable(TestLibCBOR tests/test_libcbor.cpp)
target_link_libraries(TestLibCBOR PRIVATE cbor cbor_shared cbor_serializer)

add_executable(TestTinyCBOR tests/test_tinycbor.cpp)
target_link_libraries(TestTinyCBOR PRIVATE tinycbor cbor_serializer)


#BENCHMARK LIBCBOR
add_executable(LIBCBORMapSmall libcbor/map_small.cpp)
target_link_libraries(LIBCBORMapSmall PRIVATE cbor cbor_shared cbor_serializer nonius)

add_executable(LIBCBORStudentSmall libcbor/student_small.cpp)
target_link_libraries(LIBCBORStudentSmall PRIVATE cbor cbor_shared cbor_serializer nonius)

add_executable(LIBCBORArrayBig libcbor/array_big.cpp)
target_link_libraries(LIBCBORArrayBig PRIVATE cbor cbor_shared cbor_serializer nonius)


#BENCHMARK TINYCBOR
add_executable(TINYCBORMapSmall tinycbor/map_small.cpp)
target_link_libraries(TINYCBORMapSmall PRIVATE tinycbor cbor_serializer nonius)

add_executable(TINYCBORStudentSmall tinycbor/student_small.cpp)
target_link_libraries(TINYCBORStudentSmall PRIVATE tinycbor cbor_serializer nonius)

add_executable(TINYCBORArrayBig tinycbor/array_big.cpp)
target_link_libraries(TINYCBORArrayBig PRIVATE tinycbor cbor_serializer nonius)