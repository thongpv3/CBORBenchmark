//
// Created by thongpv3 on 18/04/2017.
//

#pragma once

#include <zconf.h>
#include <map>
#include <memory>
#include <unordered_map>

namespace serializer {

    class map;
    class text;

    class item {
    public:
        using string_type = std::string;
        //todo use other data structure preserves order of insertion
        using map_type = std::map<string_type, std::shared_ptr<item>>;
        using map_ptr = std::shared_ptr<map_type>;
        using array_type = std::vector<std::shared_ptr<item>>;
        using array_ptr = std::shared_ptr<array_type>;
        using item_ptr = std::shared_ptr<item>;

        enum class item_type : int8_t {
            /* arithmetic_type store in this types: [00xx][yyyy]
            * xx = 1,2,3,4 corresponding to bitwidth = 8,16,32, 64
            * yy = 0, 1, 7 corresponding too value of UINT, NEGINT, FLOAT in cbor_type
            * */
            UINT=0, NEGINT=1, BYTE_STRING=2, TEXT_STRING=3, ARRAY=4, MAP=5, TAGGING=6, FLOAT=7
        };

        virtual item_type type() = 0;

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

    class map : public item {
    public:
        using key_type = map_type::key_type;
        using value_type = map_type::value_type;

        map_ptr items = std::make_shared<map_type>();
        template <typename T, typename ...Args>
        void insert(key_type key, T value, Args &&...args) {
            static_assert(std::is_base_of<item, T>::value, "T must derived from serializer::item");
            items->emplace(key, std::shared_ptr<T>(new T(value)));
            insert(std::forward<Args>(args)...);
        };

        template <typename T>
        void insert(key_type key, T value) {
            items->emplace(key, std::shared_ptr<T>(new T(value)));
        }

        void insert(key_type key, item_ptr p_item) {
            items->emplace(key, p_item);
        }

        template<typename T, typename ...Args>
        map(key_type key, T value, Args &&...args) {
            static_assert(std::is_base_of<item, T>::value, "T must derived from serializer::cbor_item");
            insert(key, value, std::forward<Args>(args)...);
        }

        map() {}

        item_type type() override {
            return item_type::MAP;
        }

        std::string to_string() override {
            std::string result = "{\n";
            for (auto&& it : *items) {
                result += it.first + " : " + it.second->to_string() +",\n";
            }
            return result+"}";
        }

    private:
        map_ptr value() {
            return std::shared_ptr<map_type>(items);
        }
        friend class item;
    };

    class text : public item {
    private:
        string_type v;

    public:
        using value_type = string_type;

        text(const value_type &value) : v(value) {}

        value_type value() {
            return v;
        }

        item_type type() override {
            return item_type::TEXT_STRING;
        }

        std::string to_string() override {
            return "\"" +v +"\"";
        }
    };

    class negetive_int : public item {
    public:
        using value_type = unsigned long;

    private:
        value_type v; //v represent a negative integer
        uint8_t bw;
    public:
        template <typename T>
        negetive_int(T value) : v(value>0?value:-value), bw(sizeof(T)){
            static_assert(std::is_integral<T>::value, "T must be a signed type");
        }

        template <typename T = uint32_t>
        T value() {
            static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
            return static_cast<T>(-v);
        }

        item_type type() override {
                return item_type::NEGINT;
        }

        uint8_t byte_width() {
            return bw;
        }

        std::string to_string() override {
            return std::to_string(v);
        }
    };

    class unsigned_int : public item {
    public:
        using value_type = unsigned long;

    private:
        value_type v;
        uint8_t bw;
    public:
        template <typename T>
        unsigned_int(T value) : v(value), bw(sizeof(T)){
            static_assert(std::is_unsigned<T>::value, "T must be an unsigned type");
        }

        template <typename T = unsigned>
        T value() {
            static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
            return static_cast<T>(v);
        }

        item_type type() override {
            return item_type::UINT;
        }

        uint8_t byte_width() {
            return bw;
        }

        std::string to_string() override {
            return std::to_string(v);
        }
    };

    class floating_point : public item {
    public:
        using value_type = double;

    private:
        value_type v;
        uint8_t bw;
    public:
        template <typename T>
        floating_point(T value) : v(value), bw(sizeof(T)){
            static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
        }

        template <typename T = float>
        T value() {
            static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
            return static_cast<T>(v);
        }

        item_type type() override {
            return item_type::FLOAT;
        }

        uint8_t byte_width() {
            return bw;
        }

        std::string to_string() override {
            return std::to_string(v);
        }
    };



    class array : public item {
    public:
        using value_type = array_type::value_type;

    private:
        array_ptr items = std::make_shared<array_type>();

    public:
        template <typename T, typename ...Args>
        void insert(T value, Args &&...args) {
            static_assert(std::is_base_of<item, T>::value, "T must derived from serializer::cbor_item");
            items->emplace_back(std::shared_ptr<item>(new T(value)));
            insert(std::forward<Args>(args)...);
        };

        template <typename T>
        void insert(T value) {
            items->emplace_back(std::shared_ptr<T>(new T(value)));
        }

        void insert(item_ptr ptr_item) {
            items->push_back(ptr_item);
        }

        template <typename T, typename ...Args>
        array(T value, Args&& ...args) {
            insert(value, std::forward<Args>(args)...);
        };

        array() {}

        item_type type() override {
            return item_type::ARRAY;
        }

        std::string to_string() override {
            std::string result = "[";
            for (auto it : *items) {
                result += it->to_string() + ",\n";
            }
            return result + "]";
        }

    private:
        std::shared_ptr<array_type> value() {
            return items;
        }
        friend class item;
    };

    item::map_ptr item::as_map()  {
        return static_cast<map*>(this)->value();
    }

    item::array_ptr item::as_array() {
        return static_cast<array *>(this)->value();
    }

    template<typename T>
    T item::as_signed() {
        static_assert(std::is_signed<T>::value, "T must be a signed type");
        return static_cast<T>(static_cast<negetive_int*>(this)->value());
    }

    template<typename T>
    T item::as_unsigned() {
        static_assert(std::is_unsigned<T>::value, "T must be an unsigned type");
        return static_cast<T>(static_cast<unsigned_int*>(this)->value());
    }

    template<typename T>
    T item::as_floating_point() {
        static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
        return static_cast<T>(static_cast<floating_point*>(this)->value());
    }

    item::string_type item::as_text() {
        return static_cast<text*>(this)->value();
    }

}