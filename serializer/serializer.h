//
// Created by thongpv87 on 21/04/2017.
//

#pragma once

#include <vector>
#include <memory>

namespace serializer {
    struct libcbor_serializer;
    struct tinycbor_serializer;

    template<typename T>
    class serializer_lib;

    using bytes = std::vector<char>;
}
