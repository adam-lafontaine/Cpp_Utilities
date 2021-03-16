#pragma once

#include "boost_gil.hpp"

#include <functional>

namespace libimage
{
	using fe_func_t = std::function<void(pixel_t& p)>;
	using tform_1src_func_t = std::function<pixel_t(pixel_t const& p)>;
	using tform_2src_func_t = std::function<pixel_t(pixel_t const& p1, pixel_t const& p2)>;

	namespace seq
	{
		void for_each_pixel(view_t const& view, fe_func_t const& func);

		void transform_pixels(view_t const& src, view_t const& dst, tform_1src_func_t const& func);
	}


	namespace par
	{
		void for_each_pixel(view_t const& view, fe_func_t const& func);

		void transform_pixels(view_t const& src, view_t const& dst, tform_1src_func_t const& func);
	}


	//======= GRAYSCALE OVERLOADS ================

	namespace gray
	{
		using fe_func_t = std::function<void(pixel_t& p)>;
		using tform_1src_func_t = std::function<pixel_t(pixel_t const& p)>;
		using tform_2src_func_t = std::function<pixel_t(pixel_t const& p1, pixel_t const& p2)>;
	}

	

	namespace seq
	{
		void for_each_pixel(gray::view_t const& view, gray::fe_func_t const& func);

		void transform_pixels(gray::view_t const& src, gray::view_t const& dst, gray::tform_1src_func_t const& func);
	}


	namespace par
	{
		void for_each_pixel(gray::view_t const& view, gray::fe_func_t const& func);

		void transform_pixels(gray::view_t const& src, gray::view_t const& dst, gray::tform_1src_func_t const& func);
	}
}