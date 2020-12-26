#include <functional>

using uid_func_t = std::function<void(size_t id)>;
using sid_func_t = std::function<void(long long id)>;

void for_each_in_range(size_t size, uid_func_t const& id_func);

void for_each_in_range(size_t begin, size_t end, uid_func_t const& id_func);

void for_each_in_range(long long begin, long long end, sid_func_t const& id_func);

void for_each_in_range_par(size_t size, uid_func_t const& id_func);

void for_each_in_range_par(size_t begin, size_t end, uid_func_t const& id_func);

void for_each_in_range_par(long long begin, long long end, sid_func_t const& id_func);


using uxy_func_t = std::function<void(size_t x, size_t y)>;
using sxy_func_t = std::function<void(long long x, long long y)>;

void for_each_in_range(size_t width, size_t height, uxy_func_t const&);

void for_each_in_range(long long width, long long height, sxy_func_t const&);
