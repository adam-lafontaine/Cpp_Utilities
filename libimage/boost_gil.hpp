#pragma once

// Add _CRT_SECURE_NO_WARNINGS to Preprocessor Definitions

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
//#include <boost/gil/extension/io/jpeg/old.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/color_convert.hpp>


namespace libimage
{
	namespace gil = boost::gil;

	//======= TYPE DEFINITIONS ======================

	using png_image_t = gil::rgba8_image_t;
	using png_view_t = gil::rgba8_view_t;
	using png_pixel_t = gil::rgba8_pixel_t;
	//using png_ref_t = gil::rgba8_ref_t;
	//using png_pixel_ptr_t = gil::rgba8_ptr_t;

	using jpeg_image_t = gil::rgb8_image_t;
	using jpeg_view_t = gil::rgb8_view_t;
	using jpeg_ref_t = gil::rgb8_ref_t;
	//using jpeg_pixel_t = gil::rgb8_pixel_t;
	//using jpeg_pixel_ptr_t = gil::rgb8_ptr_t;

	// using png types
	using image_t = png_image_t;
	using view_t = png_view_t;
	using pixel_t = png_pixel_t;

	using ref_t = pixel_t&;
	using pixel_ptr_t = pixel_t*;

	using pixel_ptr_list_t = std::vector<pixel_ptr_t>;
	using pixel_list_t = std::vector<pixel_t>;

	using index_t = std::ptrdiff_t;


	namespace gray
	{
		using image_t = gil::gray8_image_t;
		using view_t = gil::gray8_view_t;
		using pixel_t = gil::gray8_pixel_t;
	}
}
