//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

#include <bits/shared_ptr.h>
#include <vector>
#include <cbor.h>
#include <cbor/maps.h>
#include "cbor_item.h"

struct libcbor_serializer;
struct tinycbor_serializer;

template <typename T>
class serializer;

using bytes = std::vector<char>;

template <>
class serializer<libcbor_serializer>{
    using cbor_type = cbor_item::cbor_type;
    using cbor_item_ptr = std::shared_ptr<cbor_item>;
private:
    void static serialize_helper(cbor_item_t *root, cbor_item_ptr item) {
        switch (item->type()) {
            case cbor_type::MAP: {
                break;
            }
            case cbor_type::TEXT_STRING: {
                auto&& text= std::static_pointer_cast<cbor_text>(item)->as_text();
            }
            case cbor_type::INT: {
            }
        }
    }

public:
    bytes static serialize(cbor_item_ptr item) {
        cbor_item_t* root;
        switch (item->type()) {
            //We only support MAP or ARRAY on the root of object
            case cbor_type::MAP: {
                root = cbor_new_definite_map(item->as_map()->size());
                auto map = item->as_map();
                for (auto&& it: *map) {
                    //todo check return type
                    _cbor_map_add_key(root, cbor_build_string(it.first.c_str()));
                    serialize_helper(root, it.second);
                }
                break;
            }
            case cbor_type::ARRAY:{
                serialize_helper(root, item);
                break;
            }
            default: {
                throw std::invalid_argument("item must be pointed to cbor_array or cbor_map");
            }
        }
    }
    void static deserialize();
};
