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
    struct map_tag{};
    struct array_tag{};

    static void serialize_helper(cbor_item_t *root, cbor_item_ptr item, map_tag) {
        switch (item->type()) {
            case cbor_type::MAP: {
                break;
            }
            case cbor_type::TEXT_STRING: {
                _cbor_map_add_value(root, cbor_move(cbor_build_string(item->as_text().data())));
                break;
            }
            case cbor_type::INT: {
                _cbor_map_add_value(root, cbor_move(cbor_build_negint32((unsigned)item->as_arithmetic<int>())));
                break;
            }
        }
    }

    static void serialize_helper(cbor_item_t *root, cbor_item_ptr item, array_tag) {
        switch (item->type()) {
            case cbor_type::MAP: {
                break;
            }
            case cbor_type::TEXT_STRING: {
                cbor_array_push(root, cbor_move(cbor_build_string(item->as_text().data())));
                break;
            }
            case cbor_type::INT: {
                cbor_array_push(root, cbor_move(cbor_build_negint32((unsigned)item->as_arithmetic<int>())));
                break;
            }
        }
    }

public:
    static bytes serialize(cbor_item_ptr item) {
        cbor_item_t* root;
        bytes result;
        switch (item->type()) {
            //We only support MAP or ARRAY on the root of object
            case cbor_type::MAP: {
                map_tag tag;
                root = cbor_new_definite_map(item->as_map()->size());
                auto map = item->as_map();
                for (auto&& it: *map) {
                    _cbor_map_add_key(root, cbor_move(cbor_build_string(it.first.data())));
                    serialize_helper(root, it.second, tag);
                }
                unsigned char* buffer;
                size_t buffer_size; //lenght of buffer
                size_t length; //number of bytes after serialize
                length = cbor_serialize_alloc(root, &buffer, &buffer_size);
                result.assign(buffer, buffer+length);
                break;
            }
            case cbor_type::ARRAY:{
                array_tag tag;
                root = cbor_new_definite_array(item->as_array()->size());
                serialize_helper(root, item, tag);
                break;
            }
            default: {
                throw std::invalid_argument("item must be pointed to cbor_array or cbor_map");
            }
        }
        return result;
    }
    void static deserialize();
};
