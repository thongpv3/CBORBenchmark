add_executable(TestJsonAPI libcbor/TestAPI.cpp people.h person_info.h)
target_link_libraries(TestJsonAPI PRIVATE cbor)
