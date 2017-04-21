//
// Created by thongpv3 on 18/04/2017.
//

#pragma once

#include <zconf.h>
#include <map>
#include <memory>
#include <unordered_map>

namespace cbor {

    class cbor_map;
    class cbor_text;

    class cbor_item {
    public:
        using string_type = std::string;
        using map_type = std::unordered_map<string_type, std::shared_ptr<cbor_item>>;
        using map_ptr = std::shared_ptr<map_type>;
        using array_type = std::vector<std::shared_ptr<cbor_item>>;
        using array_ptr = std::shared_ptr<array_type>;

        enum class cbor_type : int8_t {
            /* arithmetic_type store in this format: [00xx][yyyy]
            * xx = 1,2,3,4 corresponding to bitwidth = 8,16,32, 64
            * yy = 0, 1, 7 corresponding too value of UINT, INT, FLOAT in cbor_type
            * */
            UINT=0, INT=1, BYTE_STRING=2, TEXT_STRING=3, ARRAY=4, MAP=5, TAGGING=6, FLOAT=7
        };

        virtual cbor_type type() = 0;

        map_ptr as_map();

        array_ptr as_array();

        template <typename T>
        T as_arithmetic();

        string_type as_text();

        virtual std::string to_string() = 0;
    };

    class cbor_map : public cbor_item {
    public:
        using key_type = map_type::key_type;
        using value_type = map_type::value_type;

        map_ptr items = std::make_shared<map_type>();
        template <typename T, typename ...Args>
        void insert(key_type key, T value, Args &&...args) {
            static_assert(std::is_base_of<cbor::cbor_item, T>::value, "T must derived from cbor::cbor_item");
            items->emplace(key, std::shared_ptr<T>(new T(value)));
            insert(std::forward<Args>(args)...);
        };

        template <typename T>
        void insert(key_type key, T value) {
            items->emplace(key, std::shared_ptr<T>(new T(value)));
        }

        template<typename T, typename ...Args>
        cbor_map(key_type key, T value, Args &&...args) {
            static_assert(std::is_base_of<cbor::cbor_item, T>::value, "T must derived from cbor::cbor_item");
            insert(key, value, std::forward<Args>(args)...);
        }


        cbor_map() {}

        cbor_type type() override {
            return cbor_type::MAP;
        }

        std::string to_string() override {
            std::string result = "{\n";
            for (auto&& it : *items) {
                result += it.first + " : " + it.second->to_string() +",\n";
            }
            return result+"}";
        }

    private:
        map_ptr map() {
            return std::shared_ptr<map_type>(items);
        }
        friend class cbor_item;
    };



    template<typename T>
    class cbor_arithmetic : public cbor_item {
    public:
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        using value_type = T;

    private:
        value_type v;
        uint8_t byte_width;
    public:
        cbor_arithmetic(T value) : v(value), byte_width(sizeof(T)) {}

        T value() {
            return v;
        }

        cbor_type type() override {
            cbor_type detail;
            if (std::is_signed<T>::value) {
                return cbor_type::INT;
            } else if (std::is_unsigned<T>::value) {
                return cbor_type::UINT;
            } else
                return cbor_type::FLOAT;
        }

        std::string to_string() override {
            return std::to_string(v);
        }
    };

    using cbor_float = cbor_arithmetic<float>;
    using cbor_int = cbor_arithmetic<int>;
    using cbor_byte = cbor_arithmetic<char>;

    class cbor_text : public cbor_item {
    private:
        string_type v;

    public:
        using value_type = string_type;

        cbor_text(const value_type &value) : v(value) {}

        value_type value() {
            return v;
        }

        cbor_type type() override {
            return cbor_type::TEXT_STRING;
        }

        std::string to_string() override {
            return "\"" +v +"\"";
        }
    };


    class cbor_array : public cbor_item {
    public:
        using value_type = array_type::value_type;

    private:
        array_ptr items = std::make_shared<array_type>();

    public:
        template <typename T, typename ...Args>
        void insert(T value, Args &&...args) {
            static_assert(std::is_base_of<cbor_item, T>::value, "T must derived from cbor::cbor_item");
            items->emplace_back(std::shared_ptr<cbor_item>(new T(value)));
            insert(std::forward<Args>(args)...);
        };

        template <typename T>
        void insert(T value) {
            items->emplace_back(std::shared_ptr<T>(new T(value)));
        }

        template <typename T, typename ...Args>
        cbor_array(T value, Args&& ...args) {
            insert(value, std::forward<Args>(args)...);
        };


        cbor_type type() override {
            return cbor_type::ARRAY;
        }

        std::string to_string() override {
            std::string result = "[";
            for (auto it : *items) {
                result += it->to_string() + ",\n";
            }
            return result + "]";
        }

    private:
        std::shared_ptr<array_type> array() {
            return items;
        }
        friend class cbor_item;
    };

    cbor_item::map_ptr cbor_item::as_map()  {
        return static_cast<cbor_map*>(this)->map();
    }

    cbor_item::array_ptr cbor_item::as_array() {
        return static_cast<cbor_array*>(this)->array();
    }

    template<typename T>
    T cbor_item::as_arithmetic() {
        static_assert(std::is_arithmetic<T>::value, "T must be an integral type");
        return static_cast<cbor_arithmetic<T>*>(this)->value();
    }

    cbor_item::string_type cbor_item::as_text() {
        return static_cast<cbor_text*>(this)->value();
    }

}