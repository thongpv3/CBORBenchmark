//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

#include <vector>
#include <memory>

namespace cbor {
    struct libcbor_serializer;
    struct tinycbor_serializer;

    template<typename T>
    class serializer;

    using bytes = std::vector<char>;
}
