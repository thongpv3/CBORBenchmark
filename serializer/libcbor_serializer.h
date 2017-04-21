//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

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
                case cbor_type::INT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_int>(item);
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
                case cbor_type::INT: {
                    auto&& int_ptr = std::static_pointer_cast<cbor_int>(item);
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

        void static deserialize();
    };
}