/**
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software,
 * either in source code form or as a compiledbinary, for any purpose, commercial or
 * non-commercial, and by any means.
 */

#include <ptge/ptgpak.h>

namespace ptge {
    ptg_pak_file_info::ptg_pak_file_info()
        : file_hash_id_(0)
        , data_length_(0)
        , unk8_(0)
        , attribute_(0)
        , data_offset_(0) {

    }

    bool ptg_pak_header::deserialize(std::istream &stream) {
        if (stream.read(reinterpret_cast<char*>(&header_size_), 4).gcount() != 4) {
            return false;
        }

        // Read the resource count
        if (stream.read(reinterpret_cast<char*>(&resource_count_), 4).gcount() != 4) {
            return false;
        }

        // Read each resource info
        for (std::uint32_t i = 0; i < resource_count_; i++) {
            ptg_pak_file_info info;
            if (stream.read(reinterpret_cast<char*>(&info.file_hash_id_), 4).gcount() != 4) {
                return false;
            }

            if (stream.read(reinterpret_cast<char*>(&info.data_length_), 4).gcount() != 4) {
                return false;
            }

            if (stream.read(reinterpret_cast<char*>(&info.unk8_), 4).gcount() != 4) {
                return false;
            }

            if (stream.read(reinterpret_cast<char*>(&info.attribute_), 1).gcount() != 1) {
                return false;
            }

            if (stream.read(reinterpret_cast<char*>(&info.data_offset_), 4).gcount() != 4) {
                return false;
            }
            
            infos_.push_back(info);
        }

        return true;
    }
    
    ptg_pak::ptg_pak(std::istream &stream)
        : stream_(stream) {
    }

    bool ptg_pak::deserialize() {
        if (!header_.deserialize(stream_)) {
            return false;
        }

        return true;
    }
}