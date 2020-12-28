#include "index_range.hpp"
#include "point_range_2d.hpp"
#include "for_each_in_range.hpp"

#include <algorithm>
#include <execution>


namespace for_each_in_range
{
    UnsignedPointRange2D to_unsigned_range_2d(u_point_2d const& first, u_point_2d const& last)
    {
        auto const first = UnsignedPointRange2D::pt{ first.x, first.y };
        auto const last = UnsignedPointRange2D::pt{ last.x, last.y };

        return UnsignedPointRange2D (first, last);
    }

    UnsignedPointRange2D to_unsigned_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end)
    {
        auto const first = UnsignedPointRange2D::pt{ x_begin, y_begin };
        auto const last = UnsignedPointRange2D::pt{ x_end - 1, y_end - 1 };
        
        return UnsignedPointRange2D(first, last);
    }


    SignedPointRange2D to_signed_range_2d(s_point_2d const& first, s_point_2d const& last)
    {
        return SignedPointRange2D(SignedPointRange2D::pt{ first.x, first.y }, SignedPointRange2D::pt{ last.x, last.y });
    }


    SignedPointRange2D to_signed_range_2d(s_int_t x_begin, s_int_t x_end, s_int_t y_begin, s_int_t y_end)
    {
        auto const first = SignedPointRange2D::pt{ x_begin, y_begin };
        auto const last = SignedPointRange2D::pt{ x_end - 1, y_end - 1 };

        return SignedPointRange2D(first, last);
    }


    namespace seq
    {
        static void execute(UnsignedRange& ids, u_id_func_t const& id_func)
        {
            std::for_each(ids.begin(), ids.end(), id_func);
        }


        static void execute(SignedRange& ids, s_id_func_t const& id_func)
        {
            std::for_each(ids.begin(), ids.end(), id_func);
        }


        static void execute(UnsignedPointRange2D& pts, u_pt_func_t const& pt_func)
        {
            std::for_each(pts.begin(), pts.end(), pt_func);
        }


        static void execute(SignedPointRange2D& pts, s_pt_func_t const& pt_func)
        {
            std::for_each(pts.begin(), pts.end(), pt_func);
        }



        void for_each_in_range(u_int_t size, u_id_func_t const& id_func)
        {
            UnsignedRange ids(size);
            execute(ids, id_func);
        }
        

        void for_each_in_range(u_int_t begin, u_int_t end, u_id_func_t const& id_func)
        {
            UnsignedRange ids(begin, end);
            execute(ids, id_func);
        }


        void for_each_in_range(s_int_t begin, s_int_t end, s_id_func_t const& id_func)
        {
            SignedRange ids(begin, end);
            execute(ids, id_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, u_pt_func_t const& pt_func)
        {
            UnsignedPointRange2D pts(width, height);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(u_point_2d const& first, u_point_2d const& last, u_pt_func_t const& pt_func)
        {
            auto pts = to_unsigned_range_2d(first, last);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(s_point_2d const& first, s_point_2d const& last, s_pt_func_t const& pt_func)
        {
            auto pts = to_signed_range_2d(first, last);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, u_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            for_each_in_range_2d(width, height, pt_func);
        }


        void for_each_in_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end, u_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };
            
            auto pts = to_unsigned_range_2d(x_begin, x_end, y_begin, y_end);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(s_int_t x_begin, s_int_t x_end, s_int_t y_begin, s_int_t y_end, s_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            auto pts = to_signed_range_2d(x_begin, x_end, y_begin, y_end);

            execute(pts, pt_func);
        }


        
    }


    namespace par
    {
        static void execute(UnsignedRange& ids, u_id_func_t const& id_func)
        {
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        static void execute(SignedRange& ids, s_id_func_t const& id_func)
        {
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        static void execute(UnsignedPointRange2D& pts, u_pt_func_t const& pt_func)
        {
            std::for_each(std::execution::par, pts.begin(), pts.end(), pt_func);
        }


        static void execute(SignedPointRange2D& pts, s_pt_func_t const& pt_func)
        {
            std::for_each(std::execution::par, pts.begin(), pts.end(), pt_func);
        }



        void for_each_in_range(u_int_t size, u_id_func_t const& id_func)
        {
            UnsignedRange ids(size);
            execute(ids, id_func);
        }
        

        void for_each_in_range(u_int_t begin, u_int_t end, u_id_func_t const& id_func)
        {
            UnsignedRange ids(begin, end);
            execute(ids, id_func);
        }


        void for_each_in_range(s_int_t begin, s_int_t end, s_id_func_t const& id_func)
        {
            SignedRange ids(begin, end);
            execute(ids, id_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, u_pt_func_t const& pt_func)
        {
            UnsignedPointRange2D pts(width, height);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(u_point_2d const& first, u_point_2d const& last, u_pt_func_t const& pt_func)
        {
            auto pts = to_unsigned_range_2d(first, last);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(s_point_2d const& first, s_point_2d const& last, s_pt_func_t const& pt_func)
        {
            auto pts = to_signed_range_2d(first, last);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, u_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            for_each_in_range_2d(width, height, pt_func);
        }


        void for_each_in_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end, u_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };
            
            auto pts = to_unsigned_range_2d(x_begin, x_end, y_begin, y_end);

            execute(pts, pt_func);
        }


        void for_each_in_range_2d(s_int_t x_begin, s_int_t x_end, s_int_t y_begin, s_int_t y_end, s_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            auto pts = to_signed_range_2d(x_begin, x_end, y_begin, y_end);

            execute(pts, pt_func);
        }



    }
}




























