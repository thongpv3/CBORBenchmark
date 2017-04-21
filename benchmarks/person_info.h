//
// Created by thongpv3 on 20/04/2017.
//

#pragma once

#include "../serializer/cbor_item.h"

using namespace cbor;

std::shared_ptr<cbor_item> create_map() {
    std::shared_ptr<cbor_map> map = std::make_shared<cbor_map>("_id", cbor_text("58f5f672cac5799a4fe2e414"));
    map->insert(
        "index", cbor_arithmetic<unsigned>(0),
        "guid", cbor_text("2581df5c-6b32-44e9-a06b-9e003ef2d46e"),
        "isActive", cbor_arithmetic<bool>(false),
        "balance", cbor_text("$2,749.62"),
        "picture", cbor_text("http://placehold.it/32x32"),
        "age", cbor_arithmetic<uint8_t>(32),
        "eyeColor", cbor_text("blue"),
        "name", cbor_text("Angela Carson"),
        "gender", cbor_text("female"),
        "company", cbor_text("AEORA"),
        "email", cbor_text("angelacarson@aeora.com"));
    map->insert(
        "phone", cbor_text("+1 (997) 575-3259"),
        "address", cbor_text("930 Atkins Avenue, Sunriver, Indiana, 4641"),
        "about", cbor_text("Minim adipisicing fugiat irure tempor id ipsum ex do consectetur irure laborum nostrud excepteur. Ex sint sit ex cupidatat. Ullamco sint esse id amet ullamco exercitation et voluptate.\r\n"),
        "registered", cbor_text("2015-10-19T03:44:23 -07:00"),
        "latitude", cbor_arithmetic<double>(-19.257799),
        "longitude", cbor_arithmetic<double>(-79.607493),
        "friends", cbor_array(
                    cbor_map("id", cbor_arithmetic<unsigned>(0),
                             "name", cbor_text("Agnes Welch")),
                    cbor_map("id", cbor_arithmetic<unsigned>(1),
                             "name", cbor_text("Teri Boyle")),
                    cbor_map("id", cbor_arithmetic<unsigned>(2),
                             "name", cbor_text("Willie Duke"))
            ),
        "greeting", cbor_text("Hello, Angela Carson! You have 8 unread messages."),
        "favoriteFruit", cbor_text("apple")
    );
    return map;
}