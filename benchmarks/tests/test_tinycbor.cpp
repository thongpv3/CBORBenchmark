//
// Created by thongpv3 on 22/04/2017.
//
#include <src/cbor.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <tinycbor_serializer.h>
#include <item.h>
#include "../data_generator.h"

using namespace serializer;

void test_tinycbor_serialize_simple() {
    using namespace serializer;
    std::shared_ptr<map> item = std::make_shared<map>(
            "name", text("Pham Van Thong"),
            "birthyear", unsigned_int(1995u)
    );

    auto&& result = serializer_lib<tinycbor_serializer>::serialize(item);
    std::ofstream of("test_tinycbor_serialize_simple.cbor");
    of.write(result.data(), result.size());
    of.close();
}

void test_tinycbor_serialize_student() {
    auto&& student = create_student_info();
//    std::cout << student->to_string() << std::endl;
    auto&& result = serializer_lib<tinycbor_serializer>::serialize(student);
    std::ofstream of("test_tinycbor_serialize_student.cbor");
    of.write(result.data(), result.size());
    of.close();
}

void test_tinycbor_desialize_student() {
    auto&& student = create_student_info();
//    std::cout << student->to_string() << std::endl;
    auto&& result = serializer_lib<tinycbor_serializer>::serialize(student);
    std::ofstream of("test_tinycbor_deserialize_student.cbor");
    of.write(result.data(), result.size());
    of.close();
    auto&& it = serializer_lib<tinycbor_serializer>::deserialize(result);
    std::cout << it->to_string() << std::endl;
}

void test_tinycbor_read_libcbor() {
    std::ifstream istr("test_libcbor_serializer_array.cbor");
    std::string str((std::istreambuf_iterator<char>(istr)),
                    std::istreambuf_iterator<char>());
    bytes b;
    b.assign(str.data(), str.data() + str.size());
    std::cout << serializer_lib<tinycbor_serializer>::deserialize(b)->to_string() << std::endl;
}
int main() {
//    test_tinycbor_serialize_simple();
//    test_tinycbor_serialize_student();
    test_tinycbor_read_libcbor();
    test_tinycbor_desialize_student();
    return 0;
}