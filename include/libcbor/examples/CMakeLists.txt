add_executable(readfile readfile.c)
target_link_libraries(readfile cbor)

add_executable(create_items create_items.c)
target_link_libraries(create_items cbor)

add_executable(streaming_parser streaming_parser.c)
target_link_libraries(streaming_parser cbor)

add_executable(sort sort.c)
target_link_libraries(sort cbor)

add_executable(hello hello.c)
target_link_libraries(hello cbor)

# find_package(cJSON)
#
# if(cJSON_FOUND)
#     add_executable(cjson2cbor cjson2cbor.c)
#     target_link_libraries(cjson2cbor serializer cjson)
# endif()

file(COPY data DESTINATION .)
