add_executable(TestJsonAPI libcbor/TestAPI.cpp)
target_link_libraries(TestJsonAPI PRIVATE cbor cbor_serializer)
