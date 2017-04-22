//
// Created by thongpv3 on 20/04/2017.
//

#pragma once

#include "../serializer/cbor_item.h"

using namespace cbor;

std::shared_ptr<cbor_item> create_map() {
    std::shared_ptr<cbor_map> map = std::make_shared<cbor_map>("_id", cbor_text("58f5f672cac5799a4fe2e414"));
    map->insert(
        "index", cbor_uint(0u),
        "guid", cbor_text("2581df5c-6b32-44e9-a06b-9e003ef2d46e"),
        "isActive", cbor_uint(0u),
        "balance", cbor_text("$2,749.62"),
        "picture", cbor_text("http://placehold.it/32x32"),
        "age", cbor_uint(32u),
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
        "latitude", cbor_float(-19.257799),
        "longitude", cbor_float(-79.607493),
        "friends", cbor_array(
                    cbor_map("id", cbor_uint(0u),
                             "name", cbor_text("Agnes Welch")),
                    cbor_map("id", cbor_uint(1u),
                             "name", cbor_text("Teri Boyle")),
                    cbor_map("id", cbor_uint(2u),
                             "name", cbor_text("Willie Duke"))
            ),
        "greeting", cbor_text("Hello, Angela Carson! You have 8 unread messages."),
        "favoriteFruit", cbor_text("apple")
    );
    return map;
}