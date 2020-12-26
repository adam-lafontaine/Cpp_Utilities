#include "index_range.hpp"
#include "point_range_2d.hpp"

#include <functional>
#include <algorithm>
#include <execution>

using id_func_t = std::function<void(size_t id)>;

void for_each_in_range(size_t size, id_func_t const& id_func)
{
    UnsignedRange ids(size);
	std::for_each(ids.begin(), ids.end(), id_func);
}


void for_each_in_range(size_t begin, size_t end, id_func_t const& id_func)
{
    UnsignedRange ids(begin, end);
	std::for_each(ids.begin(), ids.end(), id_func);
}


void for_each_in_range_par(size_t size, id_func_t const& id_func)
{
    UnsignedRange ids(size);
	std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
}


void for_each_in_range_par(size_t begin, size_t end, id_func_t const& id_func)
{
    UnsignedRange ids(begin, end);
	std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
}