#include <functional>


namespace for_each_in_range
{
    using u_int_t = size_t;
    using s_int_t = long long;

    using uid_func_t = std::function<void(u_int_t id)>;
    using sid_func_t = std::function<void(s_int_t id)>;

    using u_xy_func_t = std::function<void(u_int_t x, u_int_t y)>; 

    typedef struct
    {
        u_int_t x;
        u_int_t y;
    } upoint_2d;

    typedef struct
    {
        s_int_t x;
        s_int_t y;
    } spoint_2d;

    using u_pt_func_t = std::function<void(upoint_2d const&)>;
    using s_pt_func_t = std::function<void(spoint_2d const&)>;


    namespace seq
    {
        void for_each_in_range(u_int_t size, uid_func_t const& id_func);

        void for_each_in_range(u_int_t begin, u_int_t end, uid_func_t const& id_func);

        void for_each_in_range(s_int_t begin, s_int_t end, sid_func_t const& id_func);

        void for_each_in_range_2d(u_int_t width, u_int_t height, u_xy_func_t const& xy_func);

        void for_each_in_range_2d(u_int_t width, u_int_t height, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(upoint_2d const& first, upoint_2d const& last, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(spoint_2d const& first, spoint_2d const& last, s_pt_func_t const& pt_func);
    }


    namespace par
    {
        void for_each_in_range(u_int_t size, uid_func_t const& id_func);

        void for_each_in_range(u_int_t begin, u_int_t end, uid_func_t const& id_func);

        void for_each_in_range(s_int_t begin, s_int_t end, sid_func_t const& id_func);

        void for_each_in_range_2d(u_int_t width, u_int_t height, u_xy_func_t const& xy_func);

        void for_each_in_range_2d(u_int_t width, u_int_t height, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(upoint_2d const& first, upoint_2d const& last, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(spoint_2d const& first, spoint_2d const& last, s_pt_func_t const& pt_func);
    }
}
