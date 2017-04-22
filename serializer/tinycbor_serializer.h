//
// Created by thongpv3 on 22/04/2017.
//

#pragma once

#include "serializer.h"

namespace cbor {
template <>
class serializer<tinycbor_serializer> {
public:
    static void serialize(cbor_item_ptr item) {

    }

    static void deserialize(bytes buffer) {

    }
};
}