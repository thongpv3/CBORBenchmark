//
// Created by thongpv3 on 18/04/2017.
//
#include <cbor.h>
#include <vector>
#include <boost/any.hpp>
#include <iostream>
#include <fstream>
#include "../cbor_item.h"
#include "../person_info.h"
#include "../serializer.h"

template <typename T>
struct serialize;

void test_cbor_item() {
    using namespace bm;
    auto item_ptr = std::move(create_map());
    std::cout << item_ptr->to_string() << std::endl;
    std::cout << item_ptr->as_map()->at("guid")->as_text() << std::endl;
}

void test_serializer() {
    std::shared_ptr<cbor_map> item_ptr = std::make_shared<cbor_map>(
        "id", cbor_arithmetic<int>(20136495),
        "name", cbor_text("Pham Van Thong"),
        "age", cbor_arithmetic<int>(1995)
    );
    bytes buffer = serializer<libcbor_serializer>::serialize(item_ptr);
    std::ofstream of("test_serializer_output.cbor");
    of.write(buffer.data(), buffer.size());
    of.close();
}
int main() {
    using namespace bm;
    test_serializer();
    return 0;
}