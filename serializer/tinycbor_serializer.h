//
// Created by thongpv3 on 22/04/2017.
//

#pragma once

#include "serializer.h"
#include "item.h"
#include <src/cbor.h>
#include <boost/function.hpp>

#define MAX_BUFFER_SIZE 102400 //100kb

namespace serializer {
template <>
class serializer_lib<tinycbor_serializer> {
    using cbor_type = item::item_type;
//    struct map_tag_type{}
//        map_tag;
//    struct array_tag_type{}
//        array_tag;
public:
    static void serialize_helper(CborEncoder *root, std::shared_ptr<item> item) {
        switch (item->type()) {
            case cbor_type::TEXT_STRING: {
                cbor_encode_text_stringz(root, item->as_text().data());
                break;
            }
            case cbor_type::NEGINT: {
                auto&& neg_ptr = std::static_pointer_cast<negetive_int>(item);
                cbor_encode_negative_int(root, neg_ptr->value());
            }
            case cbor_type::UINT: {
                auto&& uint_ptr = std::static_pointer_cast<unsigned_int>(item);
                    cbor_encode_uint(root, uint_ptr->value());
                break;
            }
            case cbor_type::FLOAT: {
                auto&& float_ptr = std::static_pointer_cast<floating_point>(item);
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
                cbor_encoder_create_array(root, &sub_array, arr->size());
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
    static bytes serialize(std::shared_ptr<item> item) {
        bytes result;
        uint8_t buffer[MAX_BUFFER_SIZE];
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

                size_t size = cbor_encoder_get_buffer_size(&encoder, buffer);
                return bytes(buffer,buffer + size);
            }
            case cbor_type::ARRAY: {
                auto&& arr = item->as_array();
                CborEncoder array_encoder;
                cbor_encoder_create_array(&encoder, &array_encoder, arr->size());
                for (auto&& it:*arr) {
                    serialize_helper(&array_encoder, it);
                }
                cbor_encoder_close_container(&encoder, &array_encoder);

                size_t size = cbor_encoder_get_buffer_size(&encoder, buffer);
                return bytes(buffer,buffer + size);
            }
            default: {
                throw std::invalid_argument("item must be pointed to cbor_array or cbor_map");
            }
        }
    }

private:
    static std::shared_ptr<item> deserialize_helper(CborValue *value) {
        switch (cbor_value_get_type(value)) {
            case CborMapType: {
                std::shared_ptr<map> new_map = std::make_shared<map>();
                CborValue sub_map;
                size_t length;
                cbor_value_get_map_length(value, &length);
                cbor_value_enter_container(value, &sub_map);
                for (size_t i=0; i<length; i++) {
                    char *str;
                    size_t n;
                    std::string key;
                    cbor_value_dup_text_string(&sub_map, &str, &n, &sub_map);
                    key.assign(str, n);
                    new_map->insert(key, deserialize_helper(&sub_map));
                }
                cbor_value_leave_container(value, &sub_map);
                return new_map;
            }
            case CborArrayType: {
                std::shared_ptr<array> arr = std::make_shared<array>();
                CborValue sub_arr;
                size_t length;
                cbor_value_get_array_length(value, &length);
                cbor_value_enter_container(value, &sub_arr);
                for (size_t i=0; i<length; i++) {
                    arr->insert(deserialize_helper(&sub_arr));
                }
                cbor_value_leave_container(value, &sub_arr);
                return arr;
            }
            case CborTextStringType: {
                char *str;
                size_t n;
                std::string string;
                cbor_value_dup_text_string(value, &str, &n, value);
                string.assign((const char*)str, n);
                return std::make_shared<text>(string);
            }
            case CborIntegerType: {
                uint64_t v;
                cbor_value_get_raw_integer(value, &v);
                //todo cast to singed, unsigned type
                cbor_value_advance(value);
                return std::make_shared<unsigned_int>(v);
            }
            case CborFloatType: {
                float v;
                cbor_value_get_float(value, &v);
                cbor_value_advance(value);
                return std::make_shared<floating_point>(v);
            }
            case CborDoubleType: {
                double v;
                cbor_value_get_double(value, &v);
                cbor_value_advance(value);
                return std::make_shared<floating_point>(v);
            }
            default: {
                std::cerr << "Data format is not supported" << std::endl;
                throw std::exception();
            }
        }
    }

public:
    std::shared_ptr<item> static deserialize(const bytes& buffer) {
        CborParser parser;
        CborValue value;
        cbor_parser_init((const uint8_t *)buffer.data(), buffer.size(), 0, &parser, &value);
        std::shared_ptr<item> root;
        switch (cbor_value_get_type(&value)) {
            //We only support MAP or ARRAY on the root of object
            case CborMapType: {
                root = std::make_shared<map>();
                size_t length;
                cbor_value_get_map_length(&value, &length);
                CborValue sub_map;
                cbor_value_enter_container(&value, &sub_map);
                for (size_t i=0; i < length; i++) {
                    char *str;
                    size_t n;
                    std::string key;
                    cbor_value_dup_text_string(&sub_map, &str, &n, &sub_map);
                    key.assign(str, n);
                    std::static_pointer_cast<map>(root)->insert(std::move(key), deserialize_helper(&sub_map));
                }
                cbor_value_leave_container(&value, &sub_map);
                break;
            }
            case CborArrayType: {
                root = std::make_shared<array>();
                size_t length;
                cbor_value_get_array_length(&value, &length);
                CborValue sub_arr;
                cbor_value_enter_container(&value, &sub_arr);
                for (size_t i=0; i < length; i++) {
                    std::static_pointer_cast<array>(root)->insert(deserialize_helper(&sub_arr));
                }
                cbor_value_leave_container(&value, &sub_arr);
                break;
            }
            default: {
                throw std::invalid_argument("item must be pointed to cbor_array or cbor_map");
            }
        }

        return root;
    }
};
}