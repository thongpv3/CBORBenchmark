//
// Created by thongpv3 on 18/04/2017.
//
#include <cbor.h>
#include <vector>
#include <boost/any.hpp>
#include <iostream>
#include "../cbor_item.h"
#include "../person_info.h"
#include "../serializer.h"

template <typename T>
struct serialize;

void test_cbor_item() {
    using namespace bm;
    auto item_ptr = std::move(create_map());
    std::cout << item_ptr->as_map()->at("guid")->as_text() << std::endl;
}

int main() {
    using namespace bm;
    auto item_ptr = std::move(create_map());
    std::cout << item_ptr->as_map()->at("guid")->as_text() << std::endl;
    serializer<libcbor_serializer>::serialize(std::make_shared(std::move(item_ptr)));
}