//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

#include <stack>
#include <xen/xen.h>
#include "serializer.h"
#include "item.h"
#include <cbor.h>
#include <tgmath.h>

namespace serializer {
    template<>
    class serializer_lib<libcbor_serializer> {
        using cbor_type = item::item_type;
        using cbor_item_ptr = std::shared_ptr<item>;
    private:
        static cbor_item_t* serialize_helper(cbor_item_t *root, cbor_item_ptr item) {
            cbor_item_t* value;
            //todo default case
            switch (item->type()) {
                case cbor_type::TEXT_STRING: {
                    value = cbor_build_string(item->as_text().data());
                    break;
                }
                case cbor_type::NEGINT: {
                    auto&& int_ptr = std::static_pointer_cast<negetive_int>(item);
                    switch (int_ptr->byte_width()) {
                        case 4: {
                            value = cbor_build_negint32(int_ptr->value());
                        }
                        case 1: {
                            value = cbor_build_negint8(int_ptr->value<uint8_t>());
                            break;
                        }
                        case 2: {
                            value = cbor_build_negint16(int_ptr->value<uint16_t>());
                            break;
                        }
                        case 8: {
                            value = cbor_build_negint64(int_ptr->value<uint64_t>());
                            break;
                        };

                    }
                    break;
                }
                case cbor_type::UINT: {
                    auto&& int_ptr = std::static_pointer_cast<unsigned_int>(item);
                    switch (int_ptr->byte_width()) {
                        case 4: {
                            value = cbor_build_uint32(int_ptr->value());
                            break;
                        }
                        case 1: {
                            value = cbor_build_uint8(int_ptr->value<uint8_t>());
                            break;
                        }
                        case 2: {
                            value = cbor_build_uint16(int_ptr->value<uint16_t>());
                            break;
                        }
                        case 8: {
                            value = cbor_build_uint64(int_ptr->value<uint32_t>());
                            break;
                        };

                    }
                    break;
                }
                case cbor_type::FLOAT: {
                    auto&& int_ptr = std::static_pointer_cast<floating_point>(item);
                    switch (int_ptr->byte_width()) {
                        case 8: {
                            value = cbor_build_float8(int_ptr->value());
                            break;
                        }
                        case 4: {
                            value = cbor_build_float4(int_ptr->value<float>());
                            break;
                        }
                    }
                    break;
                }
                case cbor_type::MAP: {
                    auto&& map = item->as_map();
                    cbor_item_t *sub_map = cbor_new_definite_map(map->size());
                    for (auto &&it: *map) {
                        cbor_pair pair;
                        pair.key = cbor_move(cbor_build_string(it.first.data()));
                        pair.value = serialize_helper(sub_map, it.second);
                        cbor_map_add(sub_map, pair);
                    }
                    value = sub_map;
                    break;
                }
                case cbor_type::ARRAY: {
                    auto&& arr = item->as_array();
                    cbor_item_t *sub_array = cbor_new_definite_array(arr->size());
                    for (auto&& it:*arr) {
                        cbor_array_push(sub_array, serialize_helper(sub_array, it));
                    }
                    value = sub_array;
                    break;
                }
                default: {
                    std::cerr << "Unsupported type" << std::endl;
                    throw std::exception();
                }
            }
            return value;
        }

    public:
        static bytes serialize(cbor_item_ptr item) {
            cbor_item_t *root;
            switch (item->type()) {
                //We only support MAP or ARRAY on the root of object
                case cbor_type::MAP: {
                    auto &&map = item->as_map();
                    root = cbor_new_definite_map(map->size());
                    for (auto &&it: *map) {
                        cbor_pair pair;
                        pair.key = cbor_move(cbor_build_string(it.first.data()));
                        pair.value = serialize_helper(root, it.second);
                        cbor_map_add(root, pair);
                    }
                    break;
                }
                case cbor_type::ARRAY: {
                    auto&& arr = item->as_array();
                    root = cbor_new_definite_array(item->as_array()->size());
                    for (auto&& it:*arr) {
                        cbor_array_push(root, serialize_helper(root, it));
                    }
                    break;
                }
                default: {
                    throw std::invalid_argument("item must be pointed to cbor_array or cbor_map");
                }
            }

            unsigned char *buffer;
            size_t buffer_size; //lenght of buffer
            size_t length; //number of bytes after serialize
            length = cbor_serialize_alloc(root, &buffer, &buffer_size);

            bytes result;
            result.assign(buffer, buffer + length);
            return result;
        }


    private:
        static std::shared_ptr<item> deserialize_helper(cbor_item_t *cbor_it) {
            std::shared_ptr<item> new_item;
            switch(::cbor_typeof(cbor_it)) {
                case ::cbor_type::CBOR_TYPE_MAP: {
                    new_item = std::make_shared<map>();
                    cbor_pair* pairs = cbor_map_handle(cbor_it);
                    for (size_t i=0; i<cbor_map_size(cbor_it); i++) {
                        //We only support key in string type
                        std::string key = std::string((const char*)cbor_string_handle(pairs[i].key), cbor_string_length(pairs[i].key));
                        std::static_pointer_cast<map>(new_item)->insert(key, deserialize_helper(pairs[i].value));
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_ARRAY: {
                    new_item = std::make_shared<array>();
                    cbor_item_t** items = cbor_array_handle(cbor_it);
                    for (size_t i=0; i<cbor_array_size(cbor_it); i++) {
                        std::static_pointer_cast<array>(new_item)->insert(deserialize_helper(items[i]));
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_STRING: {
                    new_item = std::make_shared<text>(std::string((const char*)cbor_string_handle(cbor_it), cbor_string_length(cbor_it)));
                    break;
                }
                case ::cbor_type::CBOR_TYPE_UINT: {
                    uint8_t bw = cbor_int_get_width(cbor_it)<<2;
                    unsigned long value= cbor_get_int(cbor_it);
                    switch (bw) {
                        case 4: {
                            new_item = std::make_shared<unsigned_int>(value);
                            break;
                        }
                        case 1: {
                            new_item = std::make_shared<unsigned_int>((uint8_t)value);
                            break;
                        }
                        case 2: {
                            new_item = std::make_shared<unsigned_int>((uint16_t)value);
                            break;
                        }
                        case 8: {
                            new_item = std::make_shared<unsigned_int>((uint64_t)value);
                            break;
                        }
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_NEGINT: {
                    unsigned long value = cbor_get_int(cbor_it);
                    uint8_t bw = cbor_int_get_width(cbor_it)<<2;
                    switch (bw) {
                        case 4: {
                            new_item = std::make_shared<negetive_int>(value);
                            break;
                        }
                        case 1: {
                            new_item = std::make_shared<negetive_int>((uint8_t)value);
                            break;
                        }
                        case 2: {
                            new_item = std::make_shared<negetive_int>((uint16_t)value);
                            break;
                        }
                        case 8: {
                            new_item = std::make_shared<negetive_int>((uint64_t)value);
                            break;
                        }
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_FLOAT_CTRL: {
                    //FIXME - bad code, cast to double to prevent ambiguos error from compiler
                    uint8_t bw = std::pow((double)2, cbor_float_get_width(cbor_it));
                    switch (bw) {
                        //We must use exactly API because of floating point represent precision
                        case 8: {
                            new_item = std::make_shared<floating_point>(cbor_float_get_float8(cbor_it));
                            break;
                        }
                        case 4: {
                            new_item = std::make_shared<floating_point>(cbor_float_get_float4(cbor_it));
                            break;
                        }
                    }
                    break;
                }
                default: {
                    std::cerr << "Unsupported format" << std::endl;
                    throw std::exception();
                }
            }

            return new_item;
        }

    public:
        std::shared_ptr<item> static deserialize(const bytes& buffer) {
            cbor_load_result result;
            cbor_item_t *root = cbor_load((unsigned char*)buffer.data(), buffer.size(), &result);

            std::shared_ptr<item> it;
            switch(::cbor_typeof(root)) {
                case ::cbor_type::CBOR_TYPE_MAP: {
                    it = std::make_shared<map>();
                    cbor_pair *pairs = cbor_map_handle(root);
                    for (size_t i = 0; i < cbor_map_size(root); i++) {
                        //We only support key in string type
                        std::string key = std::string((const char *) cbor_string_handle(pairs[i].key), cbor_string_length(pairs[i].key));
                        std::static_pointer_cast<map>(it)->insert(key, deserialize_helper(pairs[i].value));
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_ARRAY: {
                    it = std::make_shared<array>();
                    cbor_item_t **items = cbor_array_handle(root);
                    for (size_t i = 0; i < cbor_array_size(root); i++) {
                        std::static_pointer_cast<array>(it)->insert(deserialize_helper(items[i]));
                    }
                    break;
                }
            }
            return it;
        }
    };
}