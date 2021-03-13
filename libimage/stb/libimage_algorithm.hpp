#pragma once

#include "image_view.hpp"

#include <functional>
#include <algorithm>
#include <execution>

namespace libimage_stb
{
	using fe_func_t = std::function<void(pixel_t const& p)>;
	using tf_1src_func_t = std::function<pixel_t(pixel_t const& p)>;
	using tf_2src_func_t = std::function<pixel_t(pixel_t const& p1, pixel_t const& p2)>;

	namespace seq
	{
		inline void for_each_pixel(image_t& image, fe_func_t const& func)
		{
			std::for_each(image.begin(), image.end(), func);
		}


		inline void for_each_pixel(view_t& view, fe_func_t const& func)
		{
			std::for_each(view.begin(), view.end(), func);
		}


		inline void transform_pixels(view_t const& src, view_t& dst, tf_1src_func_t const& func)
		{
			std::transform(src.cbegin(), src.cend(), dst.begin(), func);
		}


		inline void transform_pixels(view_t const& src1, view_t const& src2, view_t& dst, tf_2src_func_t const& func)
		{
			std::transform(src1.cbegin(), src1.cend(), src2.cbegin(), dst.begin(), func);
		}
	}


	namespace par
	{
		inline void for_each_pixel(image_t& image, fe_func_t const& func)
		{
			std::for_each(std::execution::par, image.begin(), image.end(), func);
		}


		inline void for_each_pixel(view_t& view, fe_func_t const& func)
		{
			std::for_each(std::execution::par, view.begin(), view.end(), func);
		}

		
		inline void transform_pixels(view_t const& src, view_t& dst, tf_1src_func_t const& func)
		{
			std::transform(std::execution::par, src.cbegin(), src.cend(), dst.begin(), func);
		}


		inline void transform_pixels(view_t const& src1, view_t const& src2, view_t& dst, tf_2src_func_t const& func)
		{
			std::transform(std::execution::par, src1.cbegin(), src1.cend(), src2.cbegin(), dst.begin(), func);
		}
	}


	//======= GRAYSCALE OVERLOADS ================

	namespace gray
	{
		using fe_func_t = std::function<void(pixel_t const& p)>;
		using tf_1src_func_t = std::function<pixel_t(pixel_t const& p)>;
		using tf_2src_func_t = std::function<pixel_t(pixel_t const& p1, pixel_t const& p2)>;
	}


	namespace seq
	{
		inline void for_each_pixel(gray::image_t& image, gray::fe_func_t const& func)
		{
			std::for_each(image.begin(), image.end(), func);
		}


		inline void for_each_pixel(gray::view_t& view, gray::fe_func_t const& func)
		{
			std::for_each(view.begin(), view.end(), func);
		}


		inline void transform_pixels(gray::view_t const& src, gray::view_t& dst, gray::tf_1src_func_t const& func)
		{
			std::transform(src.cbegin(), src.cend(), dst.begin(), func);
		}


		inline void transform_pixels(gray::view_t const& src1, gray::view_t const& src2, gray::view_t& dst, gray::tf_2src_func_t const& func)
		{
			std::transform(src1.cbegin(), src1.cend(), src2.cbegin(), dst.begin(), func);
		}
	}


	namespace par
	{
		inline void for_each_pixel(gray::image_t& image, gray::fe_func_t const& func)
		{
			std::for_each(std::execution::par, image.begin(), image.end(), func);
		}


		inline void for_each_pixel(gray::view_t& view, gray::fe_func_t const& func)
		{
			std::for_each(std::execution::par, view.begin(), view.end(), func);
		}


		inline void transform_pixels(gray::view_t const& src, gray::view_t& dst, gray::tf_1src_func_t const& func)
		{
			std::transform(std::execution::par, src.cbegin(), src.cend(), dst.begin(), func);
		}


		inline void transform_pixels(gray::view_t const& src1, gray::view_t const& src2, gray::view_t& dst, gray::tf_2src_func_t const& func)
		{
			std::transform(std::execution::par, src1.cbegin(), src1.cend(), src2.cbegin(), dst.begin(), func);
		}
	}
}
