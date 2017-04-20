//
// Created by thongpv3 on 18/04/2017.
//

#pragma once

#include <zconf.h>
#include <map>
#include <memory>

namespace bm {

    class cbor_map;
    class cbor_text;

    class cbor_item {
    public:
        enum class cbor_type : int8_t {
            UINT, INT, BYTE_STRING, TEXT_STRING, ARRAY, MAP, TAGGING, FLOAT
        };

        virtual cbor_type type() = 0;

        std::shared_ptr<std::map<const std::string, std::shared_ptr<cbor_item>>> as_map();
        std::shared_ptr<std::vector<std::shared_ptr<cbor_item>>> as_array();
        template <typename T>
        T as_integral();
        std::string as_text();
    };

    class cbor_map : public cbor_item {
    public:
        using key_type = const std::string;
        using value_type = std::shared_ptr<cbor_item>;
        using map_type = std::map<key_type, value_type>;

        std::shared_ptr<map_type> items = std::make_shared<map_type>();
        template <typename T, typename ...Args>
        void insert(key_type key, T value, Args &&...args) {
            static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
            items->emplace(key, std::shared_ptr<T>(new T(value)));
            insert(std::forward<Args>(args)...);
        };

        template <typename T>
        void insert(key_type key, T value) {
            items->emplace(key, std::shared_ptr<T>(new T(value)));
        }

        template<typename T, typename ...Args>
        cbor_map(key_type key, T value, Args &&...args) {
            static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
            insert(key, value, std::forward<Args>(args)...);
        }

        //todo I don't need this, remove
//        template<typename T>
//        cbor_map(key_type key, T value) {
//            static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
//            items->emplace(key, std::shared_ptr<T>(new T(value)));
//        }

        cbor_map() {}


        //old insert style
//        template<typename T, typename ...Args>
//        void insert(const key_type &key, Args &&... args) {
//            static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
//            items->emplace(key, std::make_shared<T>(std::forward<Args>(args)...));
//        }

        cbor_type type() override {
            return cbor_type::MAP;
        }

    private:
        std::shared_ptr<map_type> map() {
            return std::shared_ptr<map_type>(items);
        }
        friend class cbor_item;
    };



    template<typename T>
    class cbor_arithmetic : public cbor_item {
    public:
        static_assert(std::is_arithmetic<T>::value, "T must be an integral type");
        using value_type = T;

    private:
        value_type v;

    public:
        cbor_arithmetic(T value) : v(value) {}

        long value() {
            return v;
        }

        cbor_type type() override {
            return cbor_type::INT;
        }
    };

    class cbor_text : public cbor_item {
    private:
        std::string v;

    public:
        using value_type = std::string;

        cbor_text(const value_type &value) : v(value) {}

        value_type value() {
            return v;
        }

        cbor_type type() override {
            return cbor_type::TEXT_STRING;
        }

    };


    class cbor_array : public cbor_item {
    public:
        using value_type = std::shared_ptr<cbor_item>;
        using array_type = std::vector<value_type>;

    private:
        std::shared_ptr<std::vector<value_type>> items = std::make_shared<std::vector<value_type>>();

    public:
        template <typename T, typename ...Args>
        void insert(T value, Args &&...args) {
            static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
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

//        template<typename T>
//        void insert(std::shared_ptr<T> value) {
//            static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
//            items->emplace_back(value);
//        }

        cbor_type type() override {
            return cbor_type::ARRAY;
        }

    private:
        std::shared_ptr<array_type> array() {
            return items;
        }
        friend class cbor_item;
    };

    std::shared_ptr<std::map<const std::string, std::shared_ptr<cbor_item>>> cbor_item::as_map()  {
        return static_cast<cbor_map*>(this)->map();
    }

    std::shared_ptr<std::vector<std::shared_ptr<cbor_item>>> cbor_item::as_array() {
        return static_cast<cbor_array*>(this)->array();
    }

    template<typename T>
    T cbor_item::as_integral() {
        static_assert(std::is_arithmetic<T>::value, "T must be an integral type");
        return static_cast<cbor_arithmetic<T>*>(this)->value();
    }

    std::string cbor_item::as_text() {
        return static_cast<cbor_text*>(this)->value();
    }

}