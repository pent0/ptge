/**
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software,
 * either in source code form or as a compiledbinary, for any purpose, commercial or
 * non-commercial, and by any means.
 */

#include <ptge/ptgpak.h>
#include <iostream>
#include <fstream>

int main(const int argc, char **argv) {
    if (argc <= 1) {
        std::cout << "No pak file path specified!" << std::endl;
        return -1;
    }

    std::ifstream pak_file_stream(argv[1], std::ios_base::binary);
    if (!pak_file_stream.good()) {
        std::cout << "Can't open pak file: " << argv[1] << std::endl;
        return -1;
    }

    ptge::ptg_pak pak_file(pak_file_stream);
    if (!pak_file.deserialize()) {
        std::cout << "Failed to read pak file!" << std::endl;
        return -2;
    } 

    return 0;
}