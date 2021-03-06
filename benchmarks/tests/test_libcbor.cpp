//
// Created by thongpv3 on 18/04/2017.
//
#include <cbor.h>
#include <vector>
#include <boost/any.hpp>
#include <iostream>
#include <fstream>
#include <libcbor_serializer.h>
#include "../data_generator.h"
#include "../utils.h"

using namespace serializer;

void test_cbor_item() {
    using namespace serializer;
    auto item_ptr = std::move(create_map());
    std::cout << item_ptr->to_string() << std::endl;
    std::cout << item_ptr->as_map()->at("guid")->as_text() << std::endl;
}

void test_libcbor_serializer_map() {
    std::shared_ptr<map> item_ptr = std::make_shared<map>(
        "id", unsigned_int(20136495u),
        "name", text("Pham Van Thong"),
        "age", unsigned_int(1995u),
        "education", map(
            "university", text("Hanoi University of Science and Technology"),
            "industry", text("Computer Science")
            ),
        "friends", array(
                map("name", text("Nguyen Dinh Ky"),
                         "birthyear", unsigned_int(1994u)),
                map("name", text("Nguyen Huu Tung"),
                         "birthyear", unsigned_int(1995u))
            )
    );
    bytes buffer = serializer_lib<libcbor_serializer>::serialize(item_ptr);
    std::ofstream of("test_libcbor_serializer_map.cbor");
    of.write(buffer.data(), buffer.size());
    of.close();
}

void test_libcbor_serializer_array() {
    std::shared_ptr<array> item_ptr = std::make_shared<array>(
            map(
                    "id", unsigned_int(20136495u),
                    "name", text("Pham Van Thong"),
                    "age", unsigned_int(1995u),
                    "education", map(
                            "university", text("Hanoi University of Science and Technology"),
                            "industry", text("Computer Science")
                    ),
                    "friends", array(
                            map("name", text("Nguyen Dinh Ky"),
                                     "birthyear", unsigned_int(1994u)),
                            map("name", text("Nguyen Huu Tung"),
                                     "birthyear", unsigned_int(1995u))
                    )
            ),
            map(
                    "id", unsigned_int(20133210u),
                    "name", text("Nguyen Hoang Quan"),
                    "age", unsigned_int(1992u),
                    "education", map(
                            "university", text("Hanoi University of Science and Technology"),
                            "industry", text("Computer Science")
                    ),
                    "friends", array(
                            map("name", text("Nguyen Dinh Ky"),
                                     "birthyear", unsigned_int(1994u)),
                            map("name", text("Nguyen Huu Tung"),
                                     "birthyear", unsigned_int(1995u))
                    )
            )
    );
    bytes buffer = serializer_lib<libcbor_serializer>::serialize(item_ptr);
    std::ofstream of("test_libcbor_serializer_array.cbor");
    of.write(buffer.data(), buffer.size());
    of.close();
}

void test_libcbor_deserializer_map() {
    std::shared_ptr<map> item_ptr = std::make_shared<map>(
            "id", unsigned_int(20136495u),
            "name", text("Pham Van Thong"),
            "age", unsigned_int(1995u),
            "education", map(
                    "university", text("Hanoi University of Science and Technology"),
                    "industry", text("Computer Science")
            ),
            "friends", array(
                    map("name", text("Nguyen Dinh Ky"),
                             "birthyear", unsigned_int(1994u)),
                    map("name", text("Nguyen Huu Tung"),
                             "birthyear", unsigned_int(1995u))
            )
    );
    bytes buffer = serializer_lib<libcbor_serializer>::serialize(item_ptr);
    std::ofstream of("test_libcbor_deserializer_map.cbor");
    of.write(buffer.data(), buffer.size());
    of.close();
//    cbor_load_result result;
//    cbor_item_t *item = cbor_load((const unsigned char*)buffer.data(), buffer.size(), &result);
//    cbor_describe(item, stdout);
    std::cout << "DESER\n:" << serializer_lib<libcbor_serializer>::deserialize(buffer)->to_string() << std::endl;
}

void test_deser_simple() {
    std::shared_ptr<map> it = std::make_shared<map>(
            "name", text("Pham Van Thong"),
            "company", text("VTTEK")
    );
    std::cout << "INPUT: \n" << it->to_string() << std::endl;
    bytes  buffer = serializer_lib<libcbor_serializer>::serialize(it);
    auto&& cbor_it = serializer_lib<libcbor_serializer>::deserialize(buffer);
    std::cout << "DESER: \n" << cbor_it->to_string() << std::endl;
}

void test_serialize_big_array() {
    auto&& it = create_big_array();
    bytes&& buffer = serializer_lib<libcbor_serializer>::serialize(it);
    write_bytes_to_file("test_libcbor_serialize_big_array.cbor", buffer);
}

void test_deserialize_big_array() {
//    auto&& data = read_data_from_file("test_tinycbor_serialize_big_array.cbor");
//    auto&& data = read_data_from_file("test_libcbor_serialize_big_array.cbor");
    auto&& data = serializer_lib<libcbor_serializer>::serialize(create_map());
    write_bytes_to_file("test_libcbor_serialize_small_map.cbor", data);
    auto&& it = serializer_lib<libcbor_serializer>::deserialize(data);
    std::cout << it->to_string() << std::endl;
}
int main() {
    using namespace serializer;
    auto&& data = serializer_lib<libcbor_serializer>::serialize(create_map());
    write_bytes_to_file("small_map.cbor", data);
    data = serializer_lib<libcbor_serializer>::serialize(create_big_array());
    write_bytes_to_file("big_array.cbor", data);
//    test_serialize_big_array();
//    test_deserialize_big_array();
    /*TINYCBOR*/


    /*LIBCBOR*/
//    test_deser_simple();
//    test_libcbor_deserializer_map();
//    test_libcbor_serializer_map();
//    test_libcbor_serializer_array();


//    char buf[20];
//    memset(buf, 0, 20);
//    std::ifstream inf("test_tinycbor.cbor");
//    inf.read(buf, 16);
//    bytes buffer;
//    buffer.assign(buf, buf+6);
//    auto && item = serializer<libcbor_serializer>::deserialize(buffer);
//    std::cout << item->to_string() << std::endl;
//    inf.close();

    return 0;
}