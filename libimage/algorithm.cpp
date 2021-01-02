#include "algorithm.hpp"

#include <execution>
#include <cassert>


namespace libimage
{
	namespace seq
	{
		void for_each_pixel(view_t const& view, fe_func_t const& func)
		{
			gil::for_each_pixel(view, func);
		}


		void transform_pixels(view_t const& src, view_t const& dst, tform_1src_func_t const& func)
		{
			gil::transform_pixels(src, dst, func);
		}
	}


	namespace par
	{
		void for_each_pixel(view_t const& view, fe_func_t const& func)
		{
			if (view.is_1d_traversable())
			{
				std::for_each(std::execution::par, view.begin().x(), view.end().x(), func);
				return;
			}
			
			for (index_t y = 0; y < view.height(); ++y)
				std::for_each(std::execution::par, view.row_begin(y), view.row_end(y), func);
		}


		void transform_pixels(view_t const& src, view_t const& dst, tform_1src_func_t const& func)
		{
			assert(src.dimensions() == dst.dimensions());

			if (src.is_1d_traversable() && dst.is_1d_traversable())
			{
				std::transform(std::execution::par, src.begin().x(), src.end().x(), dst.begin().x(), func);
				return;
			}

			for (index_t y = 0; y < src.height(); ++y)
			{
				auto src_it = src.row_begin(y);
				auto dst_it = dst.row_begin(y);
				std::transform(std::execution::par, src.row_begin(y), src.row_end(y), dst.row_begin(y), func);
			}
		}
	}


	//======= GRAYSCALE OVERLOADS ================

	namespace seq
	{
		void for_each_pixel(gray::view_t const& view, gray::fe_func_t const& func)
		{
			gil::for_each_pixel(view, func);
		}


		void transform_pixels(gray::view_t const& src, gray::view_t const& dst, gray::tform_1src_func_t const& func)
		{
			gil::transform_pixels(src, dst, func);
		}
	}


	namespace par
	{
		void for_each_pixel(gray::view_t const& view, gray::fe_func_t const& func)
		{
			if (view.is_1d_traversable())
			{
				std::for_each(std::execution::par, view.begin().x(), view.end().x(), func);
				return;
			}

			for (index_t y = 0; y < view.height(); ++y)
				std::for_each(std::execution::par, view.row_begin(y), view.row_end(y), func);
		}


		void transform_pixels(gray::view_t const& src, gray::view_t const& dst, gray::tform_1src_func_t const& func)
		{
			assert(src.dimensions() == dst.dimensions());

			if (src.is_1d_traversable() && dst.is_1d_traversable())
			{
				std::transform(std::execution::par, src.begin().x(), src.end().x(), dst.begin().x(), func);
				return;
			}

			for (index_t y = 0; y < src.height(); ++y)
			{
				auto src_it = src.row_begin(y);
				auto dst_it = dst.row_begin(y);
				std::transform(std::execution::par, src.row_begin(y), src.row_end(y), dst.row_begin(y), func);
			}
		}
	}
}

