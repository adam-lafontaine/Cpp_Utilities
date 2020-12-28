#include "index_range.hpp"
#include "point_range_2d.hpp"
#include "for_each_in_range.hpp"

#include <algorithm>
#include <execution>


namespace for_each_in_range
{
    namespace seq
    {
        void for_each_in_range(u_int_t size, uid_func_t const& id_func)
        {
            UnsignedRange ids(size);
            std::for_each(ids.begin(), ids.end(), id_func);
        }
        

        void for_each_in_range(u_int_t begin, u_int_t end, uid_func_t const& id_func)
        {
            UnsignedRange ids(begin, end);
            std::for_each(ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range(s_int_t begin, s_int_t end, sid_func_t const& id_func)
        {
            SignedRange ids(begin, end);
            std::for_each(ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, uxy_func_t const& xy_func)
        {
            UnsignedPointRange2D pts(width, height);

            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            std::for_each(pts.begin(), pts.end(), pt_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, upt_func_t const& pt_func)
        {
            UnsignedPointRange2D pts(width, height);

            std::for_each(pts.begin(), pts.end(), pt_func);
        }


        void for_each_in_range_2d(upoint_2d const& first, upoint_2d const& last, upt_func_t const& pt_func)
        {
            UnsignedPointRange2D pts(UnsignedPointRange2D::pt{ first.x, first.y }, UnsignedPointRange2D::pt{ last.x, last.y });

            std::for_each(pts.begin(), pts.end(), pt_func);
        }


        void for_each_in_range_2d(spoint_2d const& first, spoint_2d const& last, spt_func_t const& pt_func)
        {
            SignedPointRange2D pts(SignedPointRange2D::pt{ first.x, first.y }, SignedPointRange2D::pt{ last.x, last.y });

            std::for_each(pts.begin(), pts.end(), pt_func);
        }
    }


    namespace par
    {
        void for_each_in_range(u_int_t size, uid_func_t const& id_func)
        {
            UnsignedRange ids(size);
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range(u_int_t begin, u_int_t end, uid_func_t const& id_func)
        {
            UnsignedRange ids(begin, end);
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range(s_int_t begin, s_int_t end, sid_func_t const& id_func)
        {
            SignedRange ids(begin, end);
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, uxy_func_t const& xy_func)
        {
            UnsignedPointRange2D pts(width, height);

            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            std::for_each(std::execution::par, pts.begin(), pts.end(), pt_func);
        }


        void for_each_in_range_2d(u_int_t width, u_int_t height, upt_func_t const& pt_func)
        {
            UnsignedPointRange2D pts(width, height);

            std::for_each(std::execution::par, pts.begin(), pts.end(), pt_func);
        }


        void for_each_in_range_2d(upoint_2d const& first, upoint_2d const& last, upt_func_t const& pt_func)
        {
            UnsignedPointRange2D pts(UnsignedPointRange2D::pt{ first.x, first.y }, UnsignedPointRange2D::pt{ last.x, last.y });

            std::for_each(std::execution::par, pts.begin(), pts.end(), pt_func);
        }


        void for_each_in_range_2d(spoint_2d const& first, spoint_2d const& last, spt_func_t const& pt_func)
        {
            SignedPointRange2D pts(SignedPointRange2D::pt{ first.x, first.y }, SignedPointRange2D::pt{ last.x, last.y });

            std::for_each(std::execution::par, pts.begin(), pts.end(), pt_func);
        }



    }
}




























