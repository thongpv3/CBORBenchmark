//
// Created by thongpv3 on 18/04/2017.
//
#include <cbor.h>
#include <vector>
#include <boost/any.hpp>
#include <iostream>
#include "../cbor_item.h"
#include "../person_info.h"

int main() {
    using namespace bm;
    auto item_ptr = std::move(create_map());
    std::cout << item_ptr->as_map()->at("guid")->as_text() << std::endl;
}

//int main() {
//    using namespace bm;
////    auto item_ptr = std::move(create_person_info());
//    std::unique_ptr<cbor_map> thong = std::move(create_map());
//    auto friends= thong->as_map()->at("friends")->as_map()->at("1")->as_map();
////    auto tung = friends->as_map()["1"]->as_map();
////    auto name = std::static_pointer_cast<cbor_text>(tung["name"]);
//    auto name = std::static_pointer_cast<cbor_text>(friends->at("name"));
//    std::cout << name->value() << std::endl;
//    std::cout << thong->as_map()->at("age")->as_integral<int>() << std::endl;
//    return 0;
//}
