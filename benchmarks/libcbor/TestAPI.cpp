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
//    auto item_ptr = std::move(create_person_info());
    std::unique_ptr<cbor_map> thong = std::move(create_map());
    auto friends= thong->as_map()->at("friends")->as_map()->at("1")->as_map();
//    auto tung = friends->as_map()["1"]->as_map();
//    auto name = std::static_pointer_cast<cbor_text>(tung["name"]);
    auto name = std::static_pointer_cast<cbor_text>(friends->at("name"));
    std::cout << name->value() << std::endl;
    std::cout << thong->as_map()->at("age")->as_integral<int>() << std::endl;
    return 0;
}

//int main() {
//    using namespace bm;
//    using cbor_type = bm::cbor_item::cbor_type;
//
//    cbor_array item;
//    item.insert(std::make_shared<cbor_integral<int>>(5));
//    item.insert(std::make_shared<cbor_text>("Hello"));
//    auto arr = item.array();
//    std::shared_ptr<cbor_integral<int>> it = std::static_pointer_cast<cbor_integral<int>>(arr[0]);
//    std::cout << it->value() << std::endl;
//
//    cbor_map map;
//    map.insert("a", std::make_shared<cbor_integral<int>>(1234));
//}

//int main() {
//    /* Preallocate the map structure */
//    cbor_m_t * root = cbor_new_definite_map(2);
//    /* Add the content */
//    cbor_map_add(root, (struct cbor_pair) {
//            .key = cbor_move(cbor_build_string("Is CBOR awesome?")),
//            .value = cbor_move(cbor_build_bool(true))
//    });
//    cbor_map_add(root, (struct cbor_pair) {
//            .key = cbor_move(cbor_build_uint8(42)),
//            .value = cbor_move(cbor_build_string("Is the answer"))
//    });
//    /* Output: `length` bytes of data in the `buffer` */
//    unsigned char * buffer;
//    size_t buffer_size,
//            length = cbor_serialize_alloc(root, &buffer, &buffer_size);
//
//    fwrite(buffer, 1, length, stdout);
//    free(buffer);
//
//    fflush(stdout);
//    cbor_decref(&root);
//}
