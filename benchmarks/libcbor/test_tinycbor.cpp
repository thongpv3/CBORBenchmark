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

int main() {
//    test_tinycbor_serialize_simple();
//    test_tinycbor_serialize_student();
    test_tinycbor_desialize_student();
    return 0;
}