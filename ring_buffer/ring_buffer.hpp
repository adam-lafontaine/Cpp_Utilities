#pragma once

#include <array>
#include <cstddef>
#include <cassert>


template <typename T, size_t SZ>
class RingBuffer
{
public:
    std::array<T, SZ> data_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t count_ = 0;
};


namespace ring_buffer
{
    template <typename T>
    class Result
    {
    public:
        bool has_item;
        T item;
    };


    inline size_t increment(size_t index, size_t sz)
    {
        return (index + 1) % sz;
    }


    template <typename T, size_t SZ>
    void push(RingBuffer<T, SZ>& buffer, T const& item)
    {
        if (buffer.count_ == SZ)
        {
            assert(false && "RingBuffer overflow not allowed");
            return;
        }

        ++buffer.count_;

        buffer.data_[buffer.tail_] = item;
        buffer.tail_ = increment(buffer.tail_, SZ);
    }


    template <typename T, size_t SZ>
    Result<T> pop(RingBuffer<T, SZ>& buffer)
    {
        if (buffer.count_ == 0)
        {
            return { false, T() };
        }

        T item = buffer.data_[buffer.head_];
        buffer.head_ = increment(buffer.head_, SZ);
        --buffer.count_;

        return { true, item };
    }


    template <typename T, size_t SZ>
    bool is_full(RingBuffer<T, SZ> const& buffer)
    {
        return buffer.count_ == SZ;
    }


    template <typename T, size_t SZ>
    bool is_empty(RingBuffer<T, SZ> const& buffer)
    {
        return buffer.count_ == 0;
    }
}
