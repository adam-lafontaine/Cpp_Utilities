#pragma once

#include "boost_gil.hpp"

#include <functional>

namespace libimage
{
	//using cpixel_func_t = std::function<void(pixel_t const& p)>;
	using pixel_func_t = std::function<void(pixel_t& p)>;;

	namespace seq
	{
		//void for_each_pixel(view_t const& view, cpixel_func_t const& func);

		void for_each_pixel(view_t const& view, pixel_func_t const& func);
	}


	namespace par
	{
		//void for_each_pixel(view_t const& view, cpixel_func_t const& func);

		void for_each_pixel(view_t const& view, pixel_func_t const& func);
	}


	//======= GRAYSCALE OVERLOADS ================

	namespace gray
	{
		using pixel_func_t = std::function<void(pixel_t& p)>;
	}

	

	namespace seq
	{
		void for_each_pixel(gray::view_t const& view, gray::pixel_func_t const& func);
	}


	namespace par
	{
		void for_each_pixel(gray::view_t const& view, gray::pixel_func_t const& func);
	}
}