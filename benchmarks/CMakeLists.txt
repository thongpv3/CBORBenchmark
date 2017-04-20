add_executable(TestJsonAPI libcbor/TestAPI.cpp cbor_item.h person_info.h serializer.h)
target_link_libraries(TestJsonAPI PRIVATE cbor)
