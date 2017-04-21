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

        template <typename T=int>
        T as_signed();

        template <typename T=unsigned>
        T as_unsigned();

        template <typename T=double>
        T as_floating_point();

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

    class cbor_int : public cbor_item {
    public:
        using value_type = long;

    private:
        value_type v;
        uint8_t bw;
    public:
        template <typename T>
        cbor_int(T value) : v(value), bw(sizeof(T)){
            static_assert(std::is_signed<T>::value, "T must be a signed type");
        }

        template <typename T = int>
        T value() {
            static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
            return static_cast<T>(v);
        }

        cbor_type type() override {
                return cbor_type::INT;
        }

        uint8_t byte_width() {
            return bw;
        }

        std::string to_string() override {
            return std::to_string(v);
        }
    };

    class cbor_uint : public cbor_item {
    public:
        using value_type = unsigned long;

    private:
        value_type v;
        uint8_t bw;
    public:
        template <typename T>
        cbor_uint(T value) : v(value), bw(sizeof(T)){
            static_assert(std::is_unsigned<T>::value, "T must be an unsigned type");
        }

        template <typename T = unsigned>
        T value() {
            static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
            return static_cast<T>(v);
        }

        cbor_type type() override {
            return cbor_type::UINT;
        }

        uint8_t byte_width() {
            return bw;
        }

        std::string to_string() override {
            return std::to_string(v);
        }
    };

    class cbor_float : public cbor_item {
    public:
        using value_type = double;

    private:
        value_type v;
        uint8_t bw;
    public:
        template <typename T>
        cbor_float(T value) : v(value), bw(sizeof(T)){
            static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
        }

        template <typename T = float>
        T value() {
            static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
            return static_cast<T>(v);
        }

        cbor_type type() override {
            return cbor_type::FLOAT;
        }

        uint8_t byte_width() {
            return bw;
        }

        std::string to_string() override {
            return std::to_string(v);
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

    template<typename T=int>
    T cbor_item::as_signed() {
        static_assert(std::is_signed<T>::value, "T must be a signed type");
        return static_cast<T>(static_cast<cbor_int*>(this)->value());
    }

    template<typename T=unsigned>
    T cbor_item::as_unsigned() {
        static_assert(std::is_unsigned<T>::value, "T must be an unsigned type");
        return static_cast<T>(static_cast<cbor_uint*>(this)->value());
    }

    template<typename T=float>
    T cbor_item::as_floating_point() {
        static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
        return static_cast<T>(static_cast<cbor_float*>(this)->value());
    }

    cbor_item::string_type cbor_item::as_text() {
        return static_cast<cbor_text*>(this)->value();
    }

}