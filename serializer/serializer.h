//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

#include <bits/shared_ptr.h>
#include <vector>
#include <cbor.h>
#include <cbor/maps.h>

namespace cbor {
    struct libcbor_serializer;
    struct tinycbor_serializer;

    template<typename T>
    class serializer;

    using bytes = std::vector<char>;
}

#include "libcbor_serializer.h"
#include "cbor_item.h"