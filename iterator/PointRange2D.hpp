#include <iterator>

class PointRange2D
{

public:
    typedef struct
    {
        size_t x;
        size_t y;
    } pt;

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = pt;
        using difference_type = std::ptrdiff_t;
        using pointer = const pt*;
        using reference = pt;

    private:
        size_t m_x_max = 0;
        size_t m_y_max = 0;

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

    iterator::value_type m_first = { 0, 0 };
    iterator::value_type m_last = { 0, 1 };

public:

    PointRange2D(size_t width, size_t height)
    {
        m_last = { width - 1, height - 1 };
    }

    iterator begin() { return iterator(m_first, m_last); }
    iterator end() { return ++(iterator(m_last, m_last)); }

};