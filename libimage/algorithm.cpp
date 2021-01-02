#include "algorithm.hpp"

#include <execution>


namespace libimage
{
	namespace seq
	{
		/*void for_each_pixel(view_t const& view, cpixel_func_t const& func)
		{
			gil::for_each_pixel(view, func);
		}*/


		void for_each_pixel(view_t const& view, pixel_func_t const& func)
		{
			gil::for_each_pixel(view, func);
		}
	}


	namespace par
	{
		/*void for_each_pixel(view_t const& view, cpixel_func_t const& func)
		{
			if (view.is_1d_traversable())
			{
				std::for_each(std::execution::par, view.begin().x(), view.end().x(), func);
			}
			else
			{
				for (std::ptrdiff_t y = 0; y < view.height(); ++y)
					std::for_each(std::execution::par, view.row_begin(y), view.row_end(y), func);
			}
		}*/


		void for_each_pixel(view_t const& view, pixel_func_t const& func)
		{
			if (view.is_1d_traversable())
			{
				std::for_each(std::execution::par, view.begin().x(), view.end().x(), func);
			}
			else
			{
				for (std::ptrdiff_t y = 0; y < view.height(); ++y)
					std::for_each(std::execution::par, view.row_begin(y), view.row_end(y), func);
			}
		}
	}


	//======= GRAYSCALE OVERLOADS ================

	namespace seq
	{
		void for_each_pixel(gray::view_t const& view, gray::pixel_func_t const& func)
		{
			gil::for_each_pixel(view, func);
		}
	}


	namespace par
	{
		void for_each_pixel(gray::view_t const& view, gray::pixel_func_t const& func)
		{
			if (view.is_1d_traversable())
			{
				std::for_each(std::execution::par, view.begin().x(), view.end().x(), func);
			}
			else
			{
				for (std::ptrdiff_t y = 0; y < view.height(); ++y)
					std::for_each(std::execution::par, view.row_begin(y), view.row_end(y), func);
			}
		}
	}
}

