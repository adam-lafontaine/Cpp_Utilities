#pragma once

#include <algorithm>
#include <functional>
#include <array>
#include <vector>

using u32 = unsigned;

template <size_t N>
using f_array = std::array<std::function<void()>, N>;

using f_vec = std::vector<std::function<void()>>;



#ifndef EXECUTE_NO_PARALLEL

#include <execution>
// -ltbb


template <size_t N>
inline void execute_parallel(f_array<N> const& f_list)
{
    std::for_each(std::execution::par, f_list.begin(), f_list.end(), [](auto const& f){ f(); });
}


inline void execute_parallel(f_vec const& f_list)
{
    std::for_each(std::execution::par, f_list.begin(), f_list.end(), [](auto const& f){ f(); });
}

#endif // !EXECUTE_NO_PARALLEL


template <size_t N>
inline void execute_sequential(f_array<N> const& f_list)
{
    std::for_each(f_list.begin(), f_list.end(), [](auto const& f){ f(); });
}


inline void execute_sequential(f_vec const& f_list)
{
    std::for_each(f_list.begin(), f_list.end(), [](auto const& f){ f(); });
}


template <size_t N>
inline void execute(f_array<N> const& f_list)
{
#ifndef EXECUTE_NO_PARALLEL

    execute_parallel(f_list);

#else

    execute_sequential(f_list);

#endif // !EXECUTE_NO_PARALLEL    
}


inline void execute(f_vec const& f_list)
{
#ifndef EXECUTE_NO_PARALLEL

    execute_parallel(f_list);

#else

    execute_sequential(f_list);

#endif // !EXECUTE_NO_PARALLEL  
}


using id_func_t = std::function<void(u32)>;


void process_range(u32 id_begin, u32 id_end, id_func_t const& id_func);

void process_range_sequential(u32 id_begin, u32 id_end, id_func_t const& id_func);