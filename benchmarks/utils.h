//
// Created by thongpv87 on 23/04/2017.
//
#include <iostream>
#include <vector>
#include <string>

using bytes = std::vector<char>;
void write_bytes_to_file(std::string file_name, bytes data) {
    std::ofstream of(file_name);
    of.write(data.data(), data.size());
    of.close();
}

bytes read_data_from_file(std::string file_name) {
    std::ifstream inf(file_name);
    std::string str((std::istreambuf_iterator<char>(inf)),
                    std::istreambuf_iterator<char>());
    bytes b;
    b.assign(str.data(), str.data() + str.size());
    return b;
}