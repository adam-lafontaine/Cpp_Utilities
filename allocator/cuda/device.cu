#include "device.hpp"

#include <cuda_runtime.h>
#include <cassert>

#define CUDA_PRINT_ERROR

#ifdef CUDA_PRINT_ERROR

#include <cstdio>

#endif


static void check_error(cudaError_t err)
{
    if(err == cudaSuccess)
    {
        return;
    }

    #ifdef CUDA_PRINT_ERROR

    printf("\n*** CUDA ERROR ***\n\n");
    printf("%s", cudaGetErrorString(err));
    printf("\n\n******************\n\n");

    #endif
}


namespace device
{
    bool malloc(MemoryBuffer& buffer, size_t n_bytes)
    {
        assert(!buffer.data);

        cudaError_t err = cudaMalloc((void**)&(buffer.data), n_bytes);
        check_error(err);

        bool result = err == cudaSuccess;

        if(result)
        {
            buffer.capacity = n_bytes;
        }
        
        return result;
    }


    bool free(MemoryBuffer& buffer)
    {
        buffer.capacity = 0;
        buffer.size = 0;

        if(buffer.data)
        {
            cudaError_t err = cudaFree(buffer.data);
            check_error(err);

            buffer.data = nullptr;

            return err == cudaSuccess;
        }

        return true;
    }


    u8* push_bytes(MemoryBuffer& buffer, size_t n_bytes)
    {
        assert(buffer.data);
        assert(buffer.capacity);
        assert(buffer.size < buffer.capacity);

        auto is_valid = 
            buffer.data &&
            buffer.capacity &&
            buffer.size < buffer.capacity;

        auto bytes_available = (buffer.capacity - buffer.size) >= n_bytes;
        assert(bytes_available);

        if(!is_valid || !bytes_available)
        {
            return nullptr;
        }

        auto data = buffer.data + buffer.size;

        buffer.size += n_bytes;

        return data;
    }


    bool pop_bytes(MemoryBuffer& buffer, size_t n_bytes)
    {
        assert(buffer.data);
        assert(buffer.capacity);
        assert(buffer.size <= buffer.capacity);
        assert(n_bytes <= buffer.capacity);
        assert(n_bytes <= buffer.size);

        auto is_valid = 
            buffer.data &&
            buffer.capacity &&
            buffer.size <= buffer.capacity &&
            n_bytes <= buffer.capacity &&
            n_bytes <= buffer.size;

        if(is_valid)
        {
            buffer.size -= n_bytes;
            return true;
        }

        return false;
    }
}