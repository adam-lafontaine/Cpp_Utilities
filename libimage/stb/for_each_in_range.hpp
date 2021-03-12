#pragma once

#include <iterator>
#include <algorithm>
#include <execution>
#include <functional>

namespace for_each_in_range_stb
{

    //======= POINT RANGE 2D ==================

    class UnsignedPointRange2D
    {
    public:

    using index_type = size_t;

    template<typename INT_T>
    struct point
    {
        INT_T x;
        INT_T y;
    };

    typedef struct point<index_type> pt;

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = pt;
        using difference_type = std::ptrdiff_t;
        using pointer = const pt*;
        using reference = const pt&;

    private:
        index_type m_x_min = 0;
        index_type m_y_min = 0;
        index_type m_x_max = 0;
        index_type m_y_max = 0;

        value_type m_loc = { 0, 0 };

    public:

        explicit iterator() {}

        explicit iterator(value_type const& first, value_type const& last)
        {
            m_loc = first;

            m_x_min = first.x;
            m_y_min = first.y;
            m_x_max = last.x;
            m_y_max = last.y;
        }

        explicit iterator(size_t width, size_t height)
        {
            m_x_max = width - 1;
            m_y_max = height - 1;
        }

        explicit iterator(value_type const& first, size_t width, size_t height)
        {
            m_loc = first;

            m_x_min = first.x;
            m_y_min = first.y;
            m_x_max = width - 1;
            m_y_max = height - 1;
        }

        iterator last()
        {
            m_loc = { m_x_max, m_y_max };
            return *this;
        }

        iterator& operator++()
        {
            ++m_loc.x;
            if (m_loc.x > m_x_max)
            {
                m_loc.x = m_x_min;
                ++m_loc.y;
            }

            return *this;
        }
        iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
        bool operator==(iterator other) const { return m_loc.x == other.m_loc.x && m_loc.y == other.m_loc.y; }
        bool operator!=(iterator other) const { return !(*this == other); }
        reference operator*() const { return m_loc; }


    };

    private:

    pt m_first = { 0, 0 };
    pt m_last = { 0, 1 };

    template<typename INT_T>
    index_type to_index(INT_T val) { return val < 0 ? 0 : static_cast<index_type>(val); }

    template<typename PT_T>
    pt to_pt(PT_T const& p) { return { to_index(p.x), to_index(p.y) }; }

    template<typename INT_T>
    index_type to_max(INT_T val) { return val < 1 ? 0 : static_cast<index_type>(val) - 1; }

    public:

    template<typename INT_T>
    UnsignedPointRange2D(INT_T width, INT_T height)
    {
        m_last = { to_max(width), to_max(height) };
    }

    template<typename INT_T>
    UnsignedPointRange2D(point<INT_T> const& first, point<INT_T> const& last)
    {
        if (last.y > first.y)
        {
            m_first = to_pt(first);
            m_last = to_pt(last);
        }
        else if (first.y > last.y)
        {
            m_first = to_pt(last);
            m_last = to_pt(first);
        }
        else if (last.x >= first.x)
        {
            m_first = to_pt(first);
            m_last = to_pt(last);
        }
        else
        {
            m_first = to_pt(last);
            m_last = to_pt(first);
        }
    }

    iterator begin() { return iterator(m_first, m_last); }
    iterator end() { return ++(iterator(m_first, m_last).last()); }

    };


    //======= FOR EACH IN RANGE ================


    using u_int_t = size_t;

    using u_xy_func_t = std::function<void(u_int_t x, u_int_t y)>;

    typedef struct
    {
        u_int_t x;
        u_int_t y;
    } u_point_2d;

    using u_pt_func_t = std::function<void(u_point_2d const&)>;

    static UnsignedPointRange2D to_unsigned_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end)
    {
        UnsignedPointRange2D::pt const first = { x_begin, y_begin };
        UnsignedPointRange2D::pt const last = { x_end - 1, y_end - 1 };

        return UnsignedPointRange2D(first, last);
    }


    namespace seq
    {
        static void execute(UnsignedPointRange2D& pts, u_pt_func_t const& pt_func)
        {
            auto const r_pt_func = [&](auto const& pt) { pt_func({ pt.x, pt.y }); };

            std::for_each(pts.begin(), pts.end(), r_pt_func);
        }
                

        inline void for_each_in_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end, u_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt) { return xy_func(pt.x, pt.y); };

            auto pts = to_unsigned_range_2d(x_begin, x_end, y_begin, y_end);

            execute(pts, pt_func);
        }

    }


    namespace par
    {
        static void execute(UnsignedPointRange2D& pts, u_pt_func_t const& pt_func)
        {
            auto const r_pt_func = [&](auto const& pt) { pt_func({ pt.x, pt.y }); };

            std::for_each(std::execution::par, pts.begin(), pts.end(), r_pt_func);
        }        


        inline void for_each_in_range_2d(u_int_t x_begin, u_int_t x_end, u_int_t y_begin, u_int_t y_end, u_xy_func_t const& xy_func)
        {
            auto const pt_func = [&](auto const& pt) { return xy_func(pt.x, pt.y); };

            auto pts = to_unsigned_range_2d(x_begin, x_end, y_begin, y_end);

            execute(pts, pt_func);
        }

    }
}