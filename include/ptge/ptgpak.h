/**
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software,
 * either in source code form or as a compiledbinary, for any purpose, commercial or
 * non-commercial, and by any means.
 */

#pragma once

#include <cstdint>
#include <fstream>
#include <vector>

namespace ptge {
    struct ptg_pak_file_info {
        enum attribute {
            attribute_compressed = 1,
            attribute_unk2 = 2
        };

        std::uint32_t file_hash_id_;
        std::uint32_t data_length_;
        std::uint32_t unk8_;
        std::uint8_t attribute_;
        std::uint32_t data_offset_;

        explicit ptg_pak_file_info();
    };

    struct ptg_pak_header {
        std::uint32_t header_size_;
        std::uint32_t resource_count_;
        std::vector<ptg_pak_file_info> infos_;

        bool deserialize(std::istream &stream);
    };

    struct ptg_pak {
    private:
        std::istream &stream_;
        ptg_pak_header header_;

    public:
        explicit ptg_pak(std::istream &stream);

        /**
         * @brief   Parse headers and metadatas.
         * 
         * The stream must be valid during the parse, and should be valid until this
         * struct is destroyed.
         * 
         * @returns True on success.
         */
        bool deserialize();
    };
}