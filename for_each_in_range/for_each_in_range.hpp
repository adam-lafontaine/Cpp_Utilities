#include <functional>

using uid_func_t = std::function<void(size_t id)>;
using sid_func_t = std::function<void(long long id)>;

void for_each_in_range(size_t size, uid_func_t const& id_func);


void for_each_in_range(size_t begin, size_t end, uid_func_t const& id_func);


void for_each_in_range(long long begin, long long end, sid_func_t const& id_func);


void for_each_in_range_par(size_t size, uid_func_t const& id_func);


void for_each_in_range_par(size_t begin, size_t end, uid_func_t const& id_func);


void for_each_in_range_par(long long begin, long long end, sid_func_t const& id_func);