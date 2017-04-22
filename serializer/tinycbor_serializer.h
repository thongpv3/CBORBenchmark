//
// Created by thongpv3 on 22/04/2017.
//

#pragma once

#include "serializer.h"
#include "cbor_item.h"
#include <src/cbor.h>

namespace cbor {
template <>
class serializer<tinycbor_serializer> {
    using cbor_type = cbor::cbor_item::cbor_type;
//    struct map_tag_type{}
//        map_tag;
//    struct array_tag_type{}
//        array_tag;
public:
    static void serialize_helper(CborEncoder *root, std::shared_ptr<cbor_item> item) {
        switch (item->type()) {
            case cbor_type::TEXT_STRING: {
                cbor_encode_text_stringz(root, item->as_text().data());
                break;
            }
            case cbor_type::NEGINT: {
                auto&& neg_ptr = std::static_pointer_cast<cbor_negint>(item);
                cbor_encode_negative_int(root, neg_ptr->value());
            }
            case cbor_type::UINT: {
                auto&& uint_ptr = std::static_pointer_cast<cbor_uint>(item);
                    cbor_encode_uint(root, uint_ptr->value());
                break;
            }
            case cbor_type::FLOAT: {
                auto&& float_ptr = std::static_pointer_cast<cbor_float>(item);
                switch (float_ptr->byte_width()) {
                    case 8: {
                        cbor_encode_double(root, float_ptr->value());
                        break;
                    }
                    case 4: {
                        cbor_encode_double(root, float_ptr->value<float>());
                        break;
                    }
                }
                break;
            }
            case cbor_type::MAP: {
                auto &&map = item->as_map();
                CborEncoder sub_map;
                cbor_encoder_create_map(root, &sub_map, map->size());
                for (auto &&it: *map) {
                    cbor_encode_text_stringz(&sub_map, it.first.data());
                    serialize_helper(&sub_map, it.second);
                }
                cbor_encoder_close_container(root, &sub_map);
                break;
            }
            case cbor_type::ARRAY: {
                auto&& arr = item->as_array();
                CborEncoder sub_array;
                for (auto&& it:*arr) {
                    serialize_helper(&sub_array, it);
                }
                cbor_encoder_close_container(root, &sub_array);
                break;
            }
        }
    }

public:
    struct parse_result {
        uint8_t* ptr;
        size_t size;

        parse_result(size_t size) : size(size), ptr(new uint8_t[size]) {
        }

        ~parse_result() {
            delete [] ptr;
        }
    };
    static bytes serialize(std::shared_ptr<cbor_item> item) {
        bytes result;
        static uint8_t buffer[1024];
        CborEncoder encoder;
        cbor_encoder_init(&encoder, buffer, sizeof(buffer), 0);
        switch (item->type()) {
            //We only support MAP or ARRAY on the root of object
            case cbor_type::MAP: {
                CborEncoder map_encoder;
                auto&& map = item->as_map();
                cbor_encoder_create_map(&encoder, &map_encoder, map->size());

                for (auto &&it: *map) {
                    cbor_encode_text_stringz(&map_encoder, it.first.data());
                    serialize_helper(&map_encoder, it.second);
//                    cbor_encode_uint(&map_encoder, 3423);
                }
                cbor_encoder_close_container(&encoder, &map_encoder);

                size_t buffer_size; //lenght of buffer
                size_t length; //number of bytes after serialize
                size_t size = cbor_encoder_get_buffer_size(&encoder, buffer);
                for (auto b : buffer) {
                    printf("%0d ", b);
                }
                return bytes(buffer,buffer + size);
            }
//            case cbor_type::ARRAY: {
//                auto&& arr = item->as_array();
//                root = cbor_new_definite_array(item->as_array()->size());
//                serialize_helper(root, item, array_tag);
//                for (auto&& it:*arr) {
//                    serialize_helper(root, it, array_tag);
//                }
//
//                unsigned char *buffer;
//                size_t buffer_size; //lenght of buffer
//                size_t length; //number of bytes after serialize
//                length = cbor_serialize_alloc(root, &buffer, &buffer_size);
//                result.assign(buffer, buffer + length);
//                break;
//            }
            default: {
                throw std::invalid_argument("item must be pointed to cbor_array or cbor_map");
            }
        }
    }

    static void deserialize(bytes buffer) {

    }
};
}