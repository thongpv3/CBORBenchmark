//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

#include <stack>
#include <xen/xen.h>
#include "serializer.h"
#include "cbor_item.h"

namespace cbor {
    template<>
    class serializer<libcbor_serializer> {
        using cbor_type = cbor_item::cbor_type;
        using cbor_item_ptr = std::shared_ptr<cbor_item>;
    private:
        struct map_tag_type{};
        struct array_tag_type{};
        static map_tag_type map_tag;
        static array_tag_type array_tag;

        static void serialize_helper(cbor_item_t *root, cbor_item_ptr item, map_tag_type) {
            switch (item->type()) {
                case cbor_type::TEXT_STRING: {
                    _cbor_map_add_value(root, cbor_move(cbor_build_string(item->as_text().data())));
                    break;
                }
                case cbor_type::NEGINT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_negint>(item);
                    switch (int_ptr->byte_width()) {
                        case 4: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_negint32(int_ptr->value())));
                            break;
                        }
                        case 1: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_negint8(int_ptr->value<char>())));
                            break;
                        }
                        case 2: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_negint16(int_ptr->value<short>())));
                            break;
                        }
                        case 8: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_negint64(int_ptr->value<long>())));
                            break;
                        };

                    }
                    break;
                }
                case cbor_type::UINT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_uint>(item);
                    switch (int_ptr->byte_width()) {
                        case 4: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_uint32(int_ptr->value())));
                            break;
                        }
                        case 1: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_uint8(int_ptr->value<uint8_t>())));
                            break;
                        }
                        case 2: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_uint16(int_ptr->value<uint16_t>())));
                            break;
                        }
                        case 8: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_uint64(int_ptr->value<uint32_t>())));
                            break;
                        };

                    }
                    break;
                }
                case cbor_type::FLOAT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_float>(item);
                    switch (int_ptr->byte_width()) {
                        case 8: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_uint32(int_ptr->value())));
                            break;
                        }
                        case 4: {
                            _cbor_map_add_value(root, cbor_move(cbor_build_uint8(int_ptr->value<float>())));
                            break;
                        }
                    }
                    break;
                }
                case cbor_type::MAP: {
                    auto &&map = item->as_map();
                    cbor_item_t *sub_map = cbor_new_definite_map(map->size());
                    for (auto &&it: *map) {
                        _cbor_map_add_key(sub_map, cbor_move(cbor_build_string(it.first.data())));
                        serialize_helper(sub_map, it.second, map_tag);
                    }
                    _cbor_map_add_value(root, sub_map);
                    break;
                }
                case cbor_type::ARRAY: {
                    auto&& arr = item->as_array();
                    cbor_item_t *sub_array = cbor_new_definite_array(arr->size());
                    for (auto&& it:*arr) {
                        serialize_helper(sub_array, it, array_tag);
                    }
                    _cbor_map_add_value(root, sub_array);
                    break;
                }
            }
        }

        static void serialize_helper(cbor_item_t *root, cbor_item_ptr item, array_tag_type) {
            switch (item->type()) {
                case cbor_type::TEXT_STRING: {
                    cbor_array_push(root, cbor_move(cbor_build_string(item->as_text().data())));
                    break;
                }
                case cbor_type::NEGINT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_negint>(item);
                    switch (int_ptr->byte_width()) {
                        case 4: {
                            cbor_array_push(root, cbor_move(cbor_build_negint32(int_ptr->value())));
                            break;
                        }
                        case 1: {
                            cbor_array_push(root, cbor_move(cbor_build_negint8(int_ptr->value<char>())));
                            break;
                        }
                        case 2: {
                            cbor_array_push(root, cbor_move(cbor_build_negint16(int_ptr->value<short>())));
                            break;
                        }
                        case 8: {
                            cbor_array_push(root, cbor_move(cbor_build_negint64(int_ptr->value<long>())));
                            break;
                        };

                    }
                    break;
                }
                case cbor_type::UINT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_uint>(item);
                    switch (int_ptr->byte_width()) {
                        case 4: {
                            cbor_array_push(root, cbor_move(cbor_build_uint32(int_ptr->value())));
                            break;
                        }
                        case 1: {
                            cbor_array_push(root, cbor_move(cbor_build_uint8(int_ptr->value<uint8_t>())));
                            break;
                        }
                        case 2: {
                            cbor_array_push(root, cbor_move(cbor_build_uint16(int_ptr->value<uint16_t>())));
                            break;
                        }
                        case 8: {
                            cbor_array_push(root, cbor_move(cbor_build_uint64(int_ptr->value<uint32_t>())));
                            break;
                        };

                    }
                    break;
                }
                case cbor_type::FLOAT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_float>(item);
                    switch (int_ptr->byte_width()) {
                        case 8: {
                            cbor_array_push(root, cbor_move(cbor_build_uint32(int_ptr->value())));
                            break;
                        }
                        case 4: {
                            cbor_array_push(root, cbor_move(cbor_build_uint8(int_ptr->value<float>())));
                            break;
                        }
                    }
                    break;
                }
                case cbor_type::MAP: {
                    auto&& map = item->as_map();
                    cbor_item_t *sub_map = cbor_new_definite_map(map->size());
                    for (auto &&it: *map) {
                        _cbor_map_add_key(sub_map, cbor_move(cbor_build_string(it.first.data())));
                        serialize_helper(sub_map, it.second, map_tag);
                    }
                    cbor_array_push(root, sub_map);
                    break;
                }
                case cbor_type::ARRAY: {
                    auto&& arr = item->as_array();
                    cbor_item_t *sub_array = cbor_new_definite_array(arr->size());
                    for (auto&& it:*arr) {
                        serialize_helper(sub_array, it, array_tag);
                    }
                    cbor_array_push(root, sub_array);
                    break;
                }
            }
        }

    public:
        static bytes serialize(cbor_item_ptr item) {
            cbor_item_t *root;
            bytes result;
            switch (item->type()) {
                //We only support MAP or ARRAY on the root of object
                case cbor_type::MAP: {
                    auto &&map = item->as_map();
                    root = cbor_new_definite_map(map->size());
                    for (auto &&it: *map) {
                        _cbor_map_add_key(root, cbor_move(cbor_build_string(it.first.data())));
                        serialize_helper(root, it.second, map_tag);
                    }

                    unsigned char *buffer;
                    size_t buffer_size; //lenght of buffer
                    size_t length; //number of bytes after serialize
                    length = cbor_serialize_alloc(root, &buffer, &buffer_size);
                    result.assign(buffer, buffer + length);
                    break;
                }
                case cbor_type::ARRAY: {
                    auto&& arr = item->as_array();
                    root = cbor_new_definite_array(item->as_array()->size());
                    serialize_helper(root, item, array_tag);
                    for (auto&& it:*arr) {
                        serialize_helper(root, it, array_tag);
                    }

                    unsigned char *buffer;
                    size_t buffer_size; //lenght of buffer
                    size_t length; //number of bytes after serialize
                    length = cbor_serialize_alloc(root, &buffer, &buffer_size);
                    result.assign(buffer, buffer + length);
                    break;
                }
                default: {
                    throw std::invalid_argument("item must be pointed to cbor_array or cbor_map");
                }
            }
            return result;
        }


    private:
        struct parse_state {
            enum class tag_type {MAP_KEY, MAP_VALUE, ARRAY};
            tag_type tag;
            std::string key;
        };

        static std::shared_ptr<cbor_item> deserialize_helper(std::shared_ptr<cbor_item> ptr_item, cbor_item_t *item, parse_state state) {
            using tag_type = parse_state::tag_type;
            std::shared_ptr<cbor_item> new_item;
            switch(::cbor_typeof(item)) {
                case ::cbor_type::CBOR_TYPE_MAP: {
                    new_item = std::make_shared<cbor_map>();
                    cbor_pair* pairs = cbor_map_handle(item);
                    for (size_t i=0; i<cbor_map_size(item); i++) {
                        //We only support key in string type
                        state.key = std::string((const char*)cbor_string_handle(pairs[i].key), cbor_string_length(pairs[i].key));
                        deserialize_helper(new_item, pairs[i].value, state);
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_ARRAY: {
                    new_item = std::make_shared<cbor_array>();
                    cbor_item_t** items = cbor_array_handle(item);
                    for (size_t i=0; i<cbor_array_size(item); i++) {
                        state.tag = tag_type::ARRAY;
                        deserialize_helper(new_item, items[i], state);
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_STRING: {
                    new_item = std::make_shared<cbor_text>(std::string((const char*)cbor_string_handle(item), cbor_string_length(item)));
                    break;
                }
                case ::cbor_type::CBOR_TYPE_UINT: {
                    uint8_t bw = cbor_int_get_width(item)<<2;
                    unsigned long value= cbor_get_int(item);
                    switch (bw) {
                        case 4: {
                            new_item = std::make_shared<cbor_uint>(value);
                            break;
                        }
                        case 1: {
                            new_item = std::make_shared<cbor_uint>((uint8_t)value);
                            break;
                        }
                        case 2: {
                            new_item = std::make_shared<cbor_uint>((uint16_t)value);
                            break;
                        }
                        case 8: {
                            new_item = std::make_shared<cbor_uint>((uint64_t)value);
                            break;
                        }
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_NEGINT: {
                    unsigned long value = cbor_get_int(item);
                    uint8_t bw = cbor_int_get_width(item)<<2;
                    switch (bw) {
                        case 4: {
                            new_item = std::make_shared<cbor_negint>(value);
                            break;
                        }
                        case 1: {
                            new_item = std::make_shared<cbor_negint>((uint8_t)value);
                            break;
                        }
                        case 2: {
                            new_item = std::make_shared<cbor_negint>((uint16_t)value);
                            break;
                        }
                        case 8: {
                            new_item = std::make_shared<cbor_negint>((uint64_t)value);
                            break;
                        }
                    }
                    break;
                }
                case ::cbor_type::CBOR_TYPE_FLOAT_CTRL: {
                    uint8_t bw = cbor_float_get_width(item)<<2;
                    switch (bw) {
                        //We must use exactly API because of floating point represent precision
                        case 8: {
                            new_item = std::make_shared<cbor_float>(cbor_float_get_float8(item));
                            break;
                        }
                        case 4: {
                            new_item = std::make_shared<cbor_float>(cbor_float_get_float4(item));
                            break;
                        }
                    }
                    break;
                }
            }

            if (ptr_item != nullptr) {
                switch (ptr_item->type()) {
                    case cbor_type::MAP: {
                        std::static_pointer_cast<cbor_map>(ptr_item)->insert(state.key, new_item);
                        break;
                    }
                    case cbor_type::ARRAY: {
                        std::static_pointer_cast<cbor_array>(ptr_item)->insert(new_item);
                        break;
                    }
                    default: {
                        std::cerr << "An rror occur" << std::endl;
                    }
                }
            } else
                ptr_item = new_item;
            return ptr_item;
        }
    public:
        std::shared_ptr<cbor_item> static deserialize(const bytes& buffer) {
            cbor_load_result result;
            cbor_item_t *root = cbor_load((unsigned char*)buffer.data(), buffer.size(), &result);
            std::shared_ptr<cbor_item> ptr_item;
            parse_state state;

            return deserialize_helper(nullptr, root, state);
        }
    };
}