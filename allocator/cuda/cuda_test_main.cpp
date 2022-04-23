#include "device.hpp"

#include <cstdio>


void malloc_free_test()
{
    printf("\nmalloc_free_test:\n");

    size_t n_bytes = 100;

    device::MemoryBuffer buffer;

    bool result;
    auto const print_result = [&](const char* label){ printf("%-18s: %4s\n", label, (result ? "PASS" : "FAIL")); };
    
    result = device::malloc(buffer, n_bytes);
    print_result("  malloc");

    if(!result)
    {
        return;
    }

    result = buffer.data;
    print_result("  malloc data");

    result = buffer.capacity == n_bytes;
    print_result("  malloc capacity");

    result = buffer.size == 0;
    print_result("  size");

    result = device::free(buffer);
    print_result("  free");

    result = !buffer.data;
    print_result("  free data");

    result = buffer.capacity == 0;
    print_result("  free capacity");

    result = buffer.size == 0;
    print_result("  free size");
}


void push_bytes_test()
{
    printf("\npush_bytes_test:\n");

    size_t n_bytes = 100;
    size_t size_a = 10;
    size_t size_b = 20;

    device::MemoryBuffer buffer;

    bool result;
    auto const print_result = [&](const char* label){ printf("  %-9s: %4s\n", label, (result ? "PASS" : "FAIL")); };

    result = device::malloc(buffer, n_bytes);
    print_result("malloc");
    if(!result)
    {
        return;
    }

    result = device::push_bytes(buffer, size_a);
    print_result("push");

    result = buffer.size == size_a;
    print_result("size");

    result = device::push_bytes(buffer, size_b);

    result = buffer.size == (size_a + size_b);
    print_result("twice");

    result = !device::push_bytes(buffer, n_bytes);
    print_result("too much");

    result = device::free(buffer);
    print_result("free");
}


void pop_bytes_test()
{
    printf("\npop_bytes_test:\n");

    size_t n_bytes = 100;
    size_t size_a = 10;
    size_t size_b = 20;

    device::MemoryBuffer buffer;

    bool result;
    auto const print_result = [&](const char* label){ printf("  %-9s: %4s\n", label, (result ? "PASS" : "FAIL")); };

    result = device::malloc(buffer, n_bytes);
    print_result("malloc");
    if(!result)
    {
        return;
    }

    result = device::push_bytes(buffer, size_b);

    result = device::pop_bytes(buffer, size_a);
    print_result("pop");

    result = buffer.size == size_b - size_a;
    print_result("size");

    result = !device::pop_bytes(buffer, size_b);
    print_result("too much");

    result = device::free(buffer);
    print_result("free");
}


int main()
{
    malloc_free_test();
    push_bytes_test();
    pop_bytes_test();
}