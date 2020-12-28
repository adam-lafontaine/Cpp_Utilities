#include "index_range.hpp"
#include "point_range_2d.hpp"
#include "for_each_in_range.hpp"

#include <algorithm>
#include <execution>


namespace for_each_in_range
{
    namespace seq
    {
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


        void for_each_in_range_2d(size_t width, size_t height, uxy_func_t const& xy_func)
        {
            UnsignedPointRange2D pts(width, height);

            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            std::for_each(pts.begin(), pts.end(), pt_func);
        }
    }


    namespace par
    {
        void for_each_in_range(size_t size, uid_func_t const& id_func)
        {
            UnsignedRange ids(size);
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range(size_t begin, size_t end, uid_func_t const& id_func)
        {
            UnsignedRange ids(begin, end);
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range(long long begin, long long end, sid_func_t const& id_func)
        {
            SignedRange ids(begin, end);
            std::for_each(std::execution::par, ids.begin(), ids.end(), id_func);
        }


        void for_each_in_range_2d(size_t width, size_t height, uxy_func_t const& xy_func)
        {
            UnsignedPointRange2D pts(width, height);

            auto const pt_func = [&](auto const& pt){ return xy_func(pt.x, pt.y); };

            std::for_each(std::execution::par, pts.begin(), pts.end(), pt_func);
        }



    }
}




























