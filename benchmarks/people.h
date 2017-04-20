//
// Created by thongpv3 on 18/04/2017.
//

#pragma once

#include <zconf.h>
#include <map>
#include <memory>

namespace bm {

class cbor_item {
public:
    enum class cbor_type : int8_t {
        UINT, INT, BYTE_STRING, TEXT_STRING, ARRAY, MAP, TAGGING, FLOAT
    };

    virtual cbor_type type() = 0;
};

template <typename T>
class cbor_integral : public cbor_item {
public:
    static_assert(std::is_integral<T>::value, "T must be an integral type");
    using value_type = T;

private:
     value_type v;

public:
    cbor_integral(T value) : v(value) {}

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

    cbor_text(const value_type& value) : v(value) {}

//    template <typename ...Args>
//    cbor_text(Args&&... args) {
//
//    }

    value_type value() {
        return v;
    }

    cbor_type type() override {
        return cbor_type::TEXT_STRING;
    }

};

class cbor_map : public cbor_item {
public:
    using key_type = const std::string;
    using value_type = std::shared_ptr<cbor_item>;
    using map_type = std::map<key_type, value_type>;

private:
    map_type items;

public:
    template <typename T, typename ...Args>
    void insert(const key_type& key, Args&&... args) {
        static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
        items.emplace(key, std::make_shared<T>(std::forward<Args>(args)...));
    }

    cbor_type type() override {
        return cbor_type::MAP;
    }

    const map_type map() {
        return items;
    }
};

class cbor_array : public cbor_item {
public:
    using value_type = std::shared_ptr<cbor_item>;
    using array_type = std::vector<value_type>;

private:
    std::vector<value_type> items;

public:
    template <typename T>
    void insert(std::shared_ptr<T> value) {
        static_assert(std::is_base_of<bm::cbor_item, T>::value, "T must derived from bm::cbor_item");
        items.emplace_back(value);
    }

    cbor_type type() override {
        return cbor_type::ARRAY;
    }

    array_type array() {
        return items;
    }
};


}