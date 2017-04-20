//
// Created by thongpv3 on 20/04/2017.
//

#pragma once

#include "people.h"

using namespace bm;

std::unique_ptr<cbor_item> create_person_info() {
    std::unique_ptr<cbor_map> map = std::make_unique<cbor_map>();
    map->insert<cbor_text>("_id","58f5f672cac5799a4fe2e414");
    return std::move(map);
}
