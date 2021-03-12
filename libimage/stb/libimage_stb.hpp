#pragma once

#include "for_each_in_range.hpp"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cstdint>
#include <functional>
#include <algorithm>
#include <execution>



using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;


namespace libimage_stb
{
	typedef struct rgba_pixel_t
	{
		union
		{
			u32 value;
			u8 channels[4];

			struct
			{
				u8 red;
				u8 green;
				u8 blue;
				u8 alpha;
			};
		};

	}rgba_pixel;

	using pixel_t = rgba_pixel;


	class rgba_image_t
	{
	public:
		u32 width = 0;
		u32 height = 0;

		rgba_pixel* data = 0;

		rgba_image_t(u32 width, u32 height) : width(width), height(height) {}

		~rgba_image_t()
		{
			if (data)
			{
				stbi_image_free(data);
			}
		}

		rgba_pixel_t* begin() { return data; }
		rgba_pixel_t* end() { return data + (u64)width * (u64)height; }
	};

	using image_t = rgba_image_t;


	class rgba_image_view_t
	{
	public:

		rgba_pixel* data = 0;
		u32 image_width = 0;

		u32 x_begin = 0;
		u32 x_end = 0;
		u32 y_begin = 0;
		u32 y_end = 0;

		u32 width = 0;
		u32 height = 0;

		pixel_t* row_begin(u32 y)
		{
			auto offset = (y_begin + y) * image_width + x_begin;
			return data + (u64)offset;
		}

	};

	using view_t = rgba_image_view_t;


	image_t read_image_from_file(const char* img_path)
	{
		int width = 0;
		int height = 0;
		int image_channels = 0;
		int forced_channels = 4;

		auto data = (rgba_pixel*)stbi_load(img_path, &width, &height, &image_channels, forced_channels);

		image_t image(width, height);
		image.data = data;

		return image;
	}


	view_t make_view(image_t& img)
	{
		view_t view;

		view.data = img.data;
		view.image_width = img.width;
		view.x_begin = 0;
		view.y_begin = 0;
		view.x_end = img.width;
		view.y_end = img.height;
		view.width = img.width;
		view.height = img.height;

		return view;
	}


	typedef struct
	{
		u32 x_begin;
		u32 x_end;
		u32 y_begin;
		u32 y_end;

	} pixel_range_t;


	view_t sub_view(view_t const& view, pixel_range_t const& range)
	{
		view_t sub_view;

		sub_view.data = view.data;
		sub_view.image_width = view.image_width;
		sub_view.x_begin = view.x_begin + range.x_begin;
		sub_view.y_begin = view.y_begin + range.y_begin;
		sub_view.x_end = view.x_end + range.x_end;
		sub_view.y_end = view.y_end + range.y_end;
		sub_view.width = range.x_end - range.x_begin;
		sub_view.height = range.y_end - range.y_begin;

		return sub_view;
	}


	using fe_func_t = std::function<void(pixel_t& p)>;


	namespace seq
	{

		void for_each_pixel(image_t& image, fe_func_t const& func)
		{
			std::for_each(image.begin(), image.end(), func);
		}


		void for_each_pixel(view_t& view, fe_func_t const& func)
		{
			auto const xy_func = [&](auto x, auto y) { return func(*(view.row_begin(y) + x));  };

			for_each_in_range::seq::for_each_in_range_2d(view.x_begin, view.x_end, view.y_begin, view.y_end, xy_func);
		}


	}


	namespace par
	{
		void for_each_pixel(image_t& image, fe_func_t const& func)
		{
			std::for_each(std::execution::par, image.begin(), image.end(), func);
		}

		void for_each_pixel(view_t& view, fe_func_t const& func)
		{
			auto const xy_func = [&](auto x, auto y) { return func(*(view.row_begin(y) + x));  };

			for_each_in_range::par::for_each_in_range_2d(view.x_begin, view.x_end, view.y_begin, view.y_end, xy_func);
		}
	}


}