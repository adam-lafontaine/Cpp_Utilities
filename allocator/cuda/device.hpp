#pragma once

#include <cstddef>
#include <cstdint>

namespace device
{
    using u8 = uint8_t;

    class MemoryBuffer
    {
    public:
        u8* data = nullptr;
        size_t capacity = 0;
        size_t size = 0;
    };


    bool malloc(MemoryBuffer& buffer, size_t n_bytes);

    bool unified_malloc(MemoryBuffer& buffer, size_t n_bytes);

    bool free(MemoryBuffer& buffer);

    u8* push_bytes(MemoryBuffer& buffer, size_t n_bytes);

    bool pop_bytes(MemoryBuffer& buffer, size_t n_bytes);
}