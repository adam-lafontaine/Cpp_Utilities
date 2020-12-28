#include <functional>


namespace for_each_in_range
{
    using u_int_t = size_t;
    using s_int_t = long long;

    using u_id_func_t = std::function<void(u_int_t id)>;
    using s_id_func_t = std::function<void(s_int_t id)>;

    using u_xy_func_t = std::function<void(u_int_t x, u_int_t y)>;
    using s_xy_func_t = std::function<void(s_int_t x, s_int_t y)>; 

    typedef struct
    {
        u_int_t x;
        u_int_t y;
    } u_point_2d;

    typedef struct
    {
        s_int_t x;
        s_int_t y;
    } s_point_2d;

    using u_pt_func_t = std::function<void(u_point_2d const&)>;
    using s_pt_func_t = std::function<void(s_point_2d const&)>;


    namespace seq
    {
        void for_each_in_range(u_int_t size, u_id_func_t const& id_func);

        void for_each_in_range(u_int_t begin, u_int_t end, u_id_func_t const& id_func);        

        void for_each_in_range(s_int_t begin, s_int_t end, s_id_func_t const& id_func);



        void for_each_in_range_2d(u_int_t width, u_int_t height, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(u_point_2d const& first, u_point_2d const& last, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(s_point_2d const& first, s_point_2d const& last, s_pt_func_t const& pt_func);



        void for_each_in_range_2d(u_int_t width, u_int_t height, u_xy_func_t const& xy_func);

        void for_each_in_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end, u_xy_func_t const& xy_func);

        void for_each_in_range_2d(s_int_t x_begin, s_int_t x_end, s_int_t y_begin, s_int_t y_end, s_xy_func_t const& xy_func);
        
    }


    namespace par
    {
        void for_each_in_range(u_int_t size, u_id_func_t const& id_func);

        void for_each_in_range(u_int_t begin, u_int_t end, u_id_func_t const& id_func);        

        void for_each_in_range(s_int_t begin, s_int_t end, s_id_func_t const& id_func);



        void for_each_in_range_2d(u_int_t width, u_int_t height, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(u_point_2d const& first, u_point_2d const& last, u_pt_func_t const& pt_func);

        void for_each_in_range_2d(s_point_2d const& first, s_point_2d const& last, s_pt_func_t const& pt_func);



        void for_each_in_range_2d(u_int_t width, u_int_t height, u_xy_func_t const& xy_func);

        void for_each_in_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end, u_xy_func_t const& xy_func);

        void for_each_in_range_2d(s_int_t x_begin, s_int_t x_end, s_int_t y_begin, s_int_t y_end, s_xy_func_t const& xy_func);
    }
}
