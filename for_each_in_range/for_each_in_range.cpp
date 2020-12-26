#include "index_range.hpp"
#include "point_range_2d.hpp"

#include <functional>
#include <algorithm>
#include <execution>

using uid_func_t = std::function<void(size_t id)>;
using sid_func_t = std::function<void(long long id)>;

void for_each_in_range(size_t size, uid_func_t const& id_func)
{
    UnsignedRange ids(size);
	std::for_each(ids.begin(), ids.end(), id_func);
}


void for_each_in_range(size_t begin, size_t end, uid_func_t const& id_func)
{
    UnsignedRange ids(begin, end);
	std::for_each(ids.begin(), ids.end(), id_func);
}


void for_each_in_range(long long begin, long long end, sid_func_t const& id_func)
{
    SignedRange ids(begin, end);
	std::for_each(ids.begin(), ids.end(), id_func);
}


void for_each_in_range_par(size_t size, uid_func_t const& id_func)
{
    UnsignedRange ids(size);
	std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
}


void for_each_in_range_par(size_t begin, size_t end, uid_func_t const& id_func)
{
    UnsignedRange ids(begin, end);
	std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
}


void for_each_in_range_par(long long begin, long long end, sid_func_t const& id_func)
{
    SignedRange ids(begin, end);
	std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
}