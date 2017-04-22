//
// Created by thongpv3 on 22/04/2017.
//
#include <src/cbor.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <tinycbor_serializer.h>
#include <cbor_item.h>



void test_tinycbor() {
    uint8_t buf[16];
    memset(buf, 0, 16);
    CborEncoder encoder;
    {
        CborEncoder mapEncoder;
        cbor_encoder_init(&encoder, buf, sizeof(buf), 0);
        cbor_encoder_create_map(&encoder, &mapEncoder, 1);
        cbor_encode_text_stringz(&mapEncoder, "foo");
        cbor_encode_boolean(&mapEncoder, true);
        cbor_encoder_close_container(&encoder, &mapEncoder);
    }

    std::ofstream of("test_tinycbor.cbor");
    of.write((const char*)buf, 6);
    of.close();

//    cbor::bytes buffer;
//    buffer.assign(buf, buf+20);
//    auto && item = cbor::serializer<cbor::libcbor_serializer>::deserialize(buffer);
//    std::cout << item->to_string() << std::endl;

    CborParser parser;
    CborValue value;
    CborValue ele;
    bool b;
    size_t i;

    printf("%p - %p - %p", buf, encoder.data.ptr, encoder.end);
    cbor_parser_init(buf, 16, 0, &parser, &value);
    cbor_value_get_map_length(&value, &i);
    std::cout << i << std::endl;
    cbor_value_map_find_value(&value, "foo", &ele);
    cbor_value_get_boolean(&ele, &b);
    std::cout << b << std::endl;
}

void test_tinycbor_serialize_simple() {
    using namespace cbor;
    std::shared_ptr<cbor_map> map = std::make_shared<cbor_map>(
            "name", cbor_text("Pham Van Thong"),
            "birthyear", cbor_uint(1995u)
    );

    auto&& result = serializer<tinycbor_serializer>::serialize(map);
    std::ofstream of("test_tinycbor_serialize_simple.cbor");
    of.write(result.data(), result.size());
    of.close();
}


int main() {
    test_tinycbor_serialize_simple();
//    test_tinycbor();
    return 0;
}