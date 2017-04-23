//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

#include <stack>
#include "serializer.h"
#include "item.h"

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
        struct parsing_context {
            enum class tag_type {MAP_KEY, MAP_VALUE, ARRAY};
            enum class container {MAP, ARRAY};
            tag_type tag;
            size_t idx, size;
            std::stack<std::shared_ptr<cbor_item>> prev_stack;
            std::stack<container> container_stack;
            std::shared_ptr<cbor_item> curr;
            std::unique_ptr<std::string> key; //store map key before we can add
        };

        using tag_type = parsing_context::tag_type;

        static void check_end_of_container(parsing_context* context) {
            if (context->idx == context->size) {
                context->curr = context->prev_stack.top();
                context->prev_stack.pop();
                context->idx = 0;
                context->size = 0;
                auto prev_container = context->container_stack.top();
                context->container_stack.pop();
                if (prev_container == parsing_context::container::MAP)
                    context->tag = tag_type::MAP_KEY;
                else if (prev_container == parsing_context::container::ARRAY)
                    context->tag = tag_type::ARRAY;
            }
        }

        static void on_map_start(void* ctx, size_t size) {
            parsing_context* context = (parsing_context*)ctx;
            auto&& map_ptr = std::make_shared<cbor_map>();

            if (context->tag == tag_type::MAP_VALUE) {
                std::static_pointer_cast<cbor_map>(context->curr)->insert(*context->key, map_ptr);
                context->idx++;
                context->tag = tag_type::MAP_KEY;
            } else if (context->tag == tag_type::ARRAY) {
                std::static_pointer_cast<cbor_array>(context->curr)->insert(map_ptr);
            }

        }

        static void on_array_start(void* ctx, size_t size) {
            parsing_context* context = (parsing_context*)ctx;
            auto&& arr_ptr = std::make_shared<cbor_array>();

            if (context->tag == tag_type::MAP_VALUE) {
                std::static_pointer_cast<cbor_map>(context->curr)->insert(*context->key, arr_ptr);
                context->tag = tag_type::MAP_KEY;
            } else if (context->tag == tag_type::ARRAY) {
                std::static_pointer_cast<cbor_array>(context->curr)->insert(arr_ptr);
            }
            context->tag = tag_type::ARRAY;
        }

        //todo static assert
        template <typename T = uint32_t>
        static void on_found_uint(void* ctx, T value) {
            parsing_context* context = (parsing_context*)ctx;
            if (context->tag == tag_type::MAP_VALUE) {
                std::static_pointer_cast<cbor_map>(context->curr)->insert(*context->key, cbor_uint(value));
                context->tag = tag_type::MAP_KEY;
            } else if (context->tag == tag_type::ARRAY) {
                std::static_pointer_cast<cbor_array>(context->curr)->insert(cbor_uint(value));
            }
        }

        template <typename T = uint32_t>
        static void on_found_negint(void* ctx, T value) {
            parsing_context* context = (parsing_context*)ctx;
            if (context->tag == tag_type::MAP_VALUE) {
                std::static_pointer_cast<cbor_map>(context->curr)->insert(*context->key, cbor_negint(value));
                context->tag = tag_type::MAP_KEY;
            } else if (context->tag == tag_type::ARRAY) {
                std::static_pointer_cast<cbor_array>(context->curr)->insert(cbor_negint(value));
            }
        }

        template <typename T = double>
        static void on_found_float(void* ctx, T value) {
            parsing_context* context = (parsing_context*)ctx;
            if (context->tag == tag_type::MAP_VALUE) {
                std::static_pointer_cast<cbor_map>(context->curr)->insert(*context->key, cbor_float(value));
                context->tag = tag_type::MAP_KEY;
            } else if (context->tag == tag_type::ARRAY) {
                std::static_pointer_cast<cbor_array>(context->curr)->insert(cbor_float(value));
            }
        }

        static void on_found_string(void* ctx, cbor_data data, size_t size) {
            parsing_context* context = (parsing_context*)ctx;
            if (context->tag == tag_type::MAP_KEY) {
                context->key = std::make_unique<std::string>((const char*)data, size);
                context->tag = tag_type::MAP_VALUE;
            } else if (context->tag == tag_type::MAP_VALUE) {
                std::static_pointer_cast<cbor_map>(context->curr)->insert(*context->key, cbor_text((const char*)data));
                context->tag = tag_type::MAP_KEY;
            } else if (context->tag == tag_type::ARRAY) {
                std::static_pointer_cast<cbor_array>(context->curr)->insert(cbor_text((const char*)data));
            }
        }
        friend struct cbor_callbacks;

    public:
        std::shared_ptr<cbor_item> static deserialize(const bytes& buffer) {
            parsing_context context;
            context.prev_stack = nullptr;
            context.curr = nullptr;
            context.idx = 0;
            context.size = 0;
            context.tag = parsing_context::tag_type::MAP_KEY;

            struct cbor_callbacks callbacks;
            callbacks.map_start = on_map_start;
            callbacks.array_start = on_array_start;
            callbacks.uint32 = on_found_uint;
            callbacks.negint32 = on_found_negint;
            callbacks.float8 = on_found_float<double>;
            callbacks.string = on_found_string;
            callbacks.byte_string = on_found_string;


            //assert cbor type is a map - todo check cbor root type

            cbor_decoder_result result;
            result.read = 0;
            cbor_data data = (const unsigned char*) buffer.data();
            do {
                data +=result.read;
                if ((const char*)data >= (buffer.data() + buffer.size()))
                    break;
                result = cbor_stream_decode(data, buffer.size(), &callbacks, &context);
            } while (result.status == CBOR_DECODER_FINISHED);
            return context.curr;
        }
    };
}