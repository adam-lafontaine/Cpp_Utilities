#include <functional>


namespace for_each_in_range
{
    using uid_func_t = std::function<void(size_t id)>;
    using sid_func_t = std::function<void(long long id)>;

    using uxy_func_t = std::function<void(size_t x, size_t y)>;
    using sxy_func_t = std::function<void(long long x, long long y)>;

    typedef struct
    {
        size_t x;
        size_t y;
    } upoint_2d;

    typedef struct
    {
        long long x;
        long long y;
    } spoint_2d;


    namespace seq
    {
        void for_each_in_range(size_t size, uid_func_t const& id_func);

        void for_each_in_range(size_t begin, size_t end, uid_func_t const& id_func);

        void for_each_in_range(long long begin, long long end, sid_func_t const& id_func);

        void for_each_in_range_2d(size_t width, size_t height, uxy_func_t const&);
    }


    namespace par
    {
        void for_each_in_range(size_t size, uid_func_t const& id_func);

        void for_each_in_range(size_t begin, size_t end, uid_func_t const& id_func);

        void for_each_in_range(long long begin, long long end, sid_func_t const& id_func);

        void for_each_in_range_2d(size_t width, size_t height, uxy_func_t const& xy_func);
    }
}
