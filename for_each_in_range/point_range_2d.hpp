#include <iterator>

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

    using pt = struct point<index_type>;

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = pt;
        using difference_type = std::ptrdiff_t;
        using pointer = const pt*;
        using reference = pt;

    private:
        index_type m_x_max = 0;
        index_type m_y_max = 0;

        value_type m_loc = { 0, 0 };

    public:

        explicit iterator() {}

        explicit iterator(value_type const& loc, value_type const& last)
        {
            m_loc = loc;
            m_x_max = last.x;
            m_y_max = last.y;
        }

        explicit iterator(value_type const& loc, size_t width, size_t height)
        {
            m_loc = loc;
            m_x_max = width - 1;
            m_y_max = height - 1;
        }

        iterator& operator++() 
        { 
            ++m_loc.x;
            if (m_loc.x > m_x_max)
            {
                m_loc.x = 0;
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
    pt to_pt(PT_T const& p) { return { to_index(p.x), to_index(p.y)}; }

public:

    template<typename INT_T>
    UnsignedPointRange2D(INT_T width, INT_T height)
    {
        m_last = { to_max(width), to_max(height) };
    }

    template<typename INT_T>
    UnsignedPointRange2D(point<INT_T> const& first, point<INT_T> const& last)
    {
        if(last.y > first.y)
        {
            m_first = to_pt(first);
            m_last = to_pt(last);
        }
        else if(first.y > last.y)
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
    iterator end() { return ++(iterator(m_last, m_last)); }

};


class SignedPointRange2D
{
public:

    using index_type = long long;

    template<typename INT_T>
    struct point
    {
        INT_T x;
        INT_T y;
    };

    using pt = struct point<index_type>;

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = pt;
        using difference_type = std::ptrdiff_t;
        using pointer = const pt*;
        using reference = pt;

    private:
        index_type m_x_max = 0;
        index_type m_y_max = 0;

        value_type m_loc = { 0, 0 };

    public:

        explicit iterator() {}

        explicit iterator(value_type const& loc, value_type const& last)
        {
            m_loc = loc;
            m_x_max = last.x;
            m_y_max = last.y;
        }

        explicit iterator(value_type const& loc, size_t width, size_t height)
        {
            m_loc = loc;
            m_x_max = width - 1;
            m_y_max = height - 1;
        }

        iterator& operator++() 
        { 
            ++m_loc.x;
            if (m_loc.x > m_x_max)
            {
                m_loc.x = 0;
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
    index_type to_index(INT_T val) { return static_cast<index_type>(val); }

    template<typename PT_T>
    pt to_pt(PT_T const& p) { return { to_index(p.x), to_index(p.y)}; }

public:

    template<typename INT_T>
    SignedPointRange2D(INT_T width, INT_T height)
    {
        m_last = { to_max(width), to_max(height) };
    }

    template<typename INT_T>
    SignedPointRange2D(point<INT_T> const& first, point<INT_T> const& last)
    {
        if(last.y > first.y)
        {
            m_first = to_pt(first);
            m_last = to_pt(last);
        }
        else if(first.y > last.y)
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
    iterator end() { return ++(iterator(m_last, m_last)); }

};