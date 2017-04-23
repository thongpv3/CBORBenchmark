//
// Created by thongpv87 on 23/04/2017.
//

#include <nonius/nonius.h++>
#define NONIUS_RUNNER
#include <nonius/main.h++>
#include <libcbor_serializer.h>
#include "../data_generator.h"

NONIUS_BENCHMARK("LIBCBOR - map:small - serialize", [](nonius::chronometer meter){
    using namespace serializer;
    const auto&& item = create_big_array();
    meter.measure([item]{
        serializer_lib<libcbor_serializer>::serialize(item);
    });
})