//
// Created by thongpv3 on 20/04/2017.
//

#pragma once

#include "people.h"

using namespace bm;

std::unique_ptr<cbor_item> create_person_info() {
    std::unique_ptr<cbor_map> map = std::make_unique<cbor_map>();
    map->insert<cbor_text>("_id","58f5f672cac5799a4fe2e414");
    map->insert<cbor_integral<uint>>("index", 0);
    map->insert<cbor_text>("guid", "2581df5c-6b32-44e9-a06b-9e003ef2d46e");
    map->insert<cbor_integral<char>>("isActive", 0);
    map->insert<cbor_text>("balance", "$2,749.62");
    map->insert<cbor_text>("picture", "http://placehold.it/32x32");
    return std::move(map);
}
