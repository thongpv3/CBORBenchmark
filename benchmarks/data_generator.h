//
// Created by thongpv3 on 20/04/2017.
//

#pragma once

#include "item.h"

std::shared_ptr<serializer::item> create_map() {
    using namespace serializer;
    std::shared_ptr<map> item = std::make_shared<map>("_id", text("58f5f672cac5799a4fe2e414"));
    item->insert(
        "index", unsigned_int(0u),
        "guid", text("2581df5c-6b32-44e9-a06b-9e003ef2d46e"),
        "isActive", unsigned_int(0u),
        "balance", text("$2,749.62"),
        "picture", text("http://placehold.it/32x32"),
        "age", unsigned_int(32u),
        "eyeColor", text("blue"),
        "name", text("Angela Carson"),
        "gender", text("female"),
        "company", text("AEORA"),
        "email", text("angelacarson@aeora.com"));
    item->insert(
        "phone", text("+1 (997) 575-3259"),
        "address", text("930 Atkins Avenue, Sunriver, Indiana, 4641"),
        "about", text("Minim adipisicing fugiat irure tempor id ipsum ex do consectetur irure laborum nostrud excepteur. Ex sint sit ex cupidatat. Ullamco sint esse id amet ullamco exercitation et voluptate.\r\n"),
        "registered", text("2015-10-19T03:44:23 -07:00"),
        "latitude", floating_point(-19.257799),
        "longitude", floating_point(-79.607493),
        "friends", array(
                    map("id", unsigned_int(0u),
                             "name", text("Agnes Welch")),
                    map("id", unsigned_int(1u),
                             "name", text("Teri Boyle")),
                    map("id", unsigned_int(2u),
                             "name", text("Willie Duke"))
            ),
        "greeting", text("Hello, Angela Carson! You have 8 unread messages."),
        "favoriteFruit", text("apple")
    );
    return item;
}

std::shared_ptr<serializer::map> create_student_info() {
    using namespace serializer;
    return std::make_shared<map>(
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
}

std::shared_ptr<serializer::array> create_big_array() {
    using namespace serializer;
    auto&& m = create_map();
    std::shared_ptr<array> arr = std::make_shared<array>();
    for (int i=1; i<100; i++) {
        arr->insert(m);
    }
    return arr;
}