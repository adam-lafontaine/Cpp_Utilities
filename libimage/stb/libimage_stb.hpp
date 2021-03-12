#pragma once

#include "image_view.hpp"

#include <cstdint>
#include <functional>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;


namespace libimage_stb
{
	image_t read_image_from_file(const char* img_path);

	view_t make_view(image_t& img);

	view_t sub_view(image_t& image, pixel_range_t const& range);

	view_t sub_view(view_t const& view, pixel_range_t const& range);

	view_t row_view(image_t& image, u32 y);

	view_t row_view(view_t& view, u32 y);


	namespace gray
	{
		image_t read_image_from_file(const char* img_path);		
	}

	namespace grey = gray;


	//======= GRAYSCALE OVERLOADS ================

	gray::view_t make_view(gray::image_t& img);

	gray::view_t sub_view(gray::image_t& image, pixel_range_t const& range);

	gray::view_t sub_view(gray::view_t const& view, pixel_range_t const& range);

	gray::view_t row_view(gray::image_t& image, u32 y);

	gray::view_t row_view(gray::view_t& view, u32 y);
}