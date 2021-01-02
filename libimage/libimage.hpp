#pragma once

#include "conversions.hpp"

// Add _CRT_SECURE_NO_WARNINGS to Preprocessor Definitions

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
//#include <boost/gil/extension/io/jpeg/old.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/color_convert.hpp>

namespace gil = boost::gil;

#include <vector>
#include <string>
#include <functional>
#include <filesystem>

namespace libimage
{
	using file_path_t = std::filesystem::path;


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
	

	constexpr size_t CHANNEL_SIZE = 256; // 8 bit channel
	constexpr auto IMAGE_FILE_EXTENSION = ".png";


	typedef struct
	{
		index_t x_begin;
		index_t x_end;
		index_t y_begin;
		index_t y_end;
	} pixel_range_t;

	//using range_list_t = std::vector<pixel_range_t>;

	//using rgb_list_t = std::vector<rgb_t>;

	//using rgba_list_t = std::vector<rgba_t>;	


	//======= READ IMAGES =====================

	image_t read_image_from_file(file_path_t const& img_path);

	
	//====== MAKE VIEWS ====================

	view_t make_view(image_t& img);
	
	view_t make_resized_view(image_t& img_src, image_t& img_dst);

	view_t sub_view(view_t const& view, pixel_range_t const& range);

	view_t column_view(view_t const& view, size_t x);

	view_t row_view(view_t const& view, size_t y);

	view_t column_view(view_t const& view, index_t y_begin, index_t y_end, index_t x);

	view_t row_view(view_t const& view, index_t x_begin, index_t x_end, index_t y);


	//======= WRITE IMAGES =====================

	void write_image_view(file_path_t const& file_path, view_t const& view);
	


	//======= CONVERSION FUNCTIONS ==============	

	bits32 to_bits32(pixel_t const& src);
	
	bits32 to_bits32(ref_t const& src);

	bits32 to_bits32(pixel_ptr_t const& ptr);

	rgb_t to_rgb(pixel_t const& pixel);

	rgba_t to_rgba(pixel_t const& pixel);

	pixel_t to_pixel(bits8 r, bits8 g, bits8 b, bits8 a = 255);

	pixel_t to_pixel(rgb_t const& rgb);

	pixel_t to_pixel(rgba_t const& rgba);

	/*rgb_list_t to_rgb_column(view_t const& img_v, index_t y_begin, index_t y_end, index_t x);

	rgb_list_t to_rgb_column(view_t const& img_v, index_t x);

	rgb_list_t to_rgb_row(view_t const& img_v, index_t x_begin, index_t x_end, index_t y);

	rgb_list_t to_rgb_row(view_t const& img_v, index_t y);*/



	namespace gray
	{
		using image_t = gil::gray8_image_t;
		using view_t = gil::gray8_view_t;
		using pixel_t = gil::gray8_pixel_t;

		image_t read_image_from_file(file_path_t const& img_path);


		using hist_t = std::array<unsigned, CHANNEL_SIZE>; // histogram of shades of gray

		hist_t make_histogram(view_t const& view);
	}

	namespace grey = gray;


	//======= GRAYSCALE OVERLOADS ================

	gray::view_t make_view(gray::image_t& img);

	gray::view_t make_resized_view(gray::image_t& img_src, gray::image_t& img_dst);

	gray::view_t sub_view(gray::view_t const& view, pixel_range_t const& range);

	gray::view_t column_view(gray::view_t const& view, size_t x);

	gray::view_t row_view(gray::view_t const& view, size_t y);

	gray::view_t column_view(gray::view_t const& view, index_t y_begin, index_t y_end, index_t x);

	gray::view_t row_view(gray::view_t const& view, index_t x_begin, index_t x_end, index_t y);

	void write_image_view(file_path_t const& file_path, gray::view_t const& view);


	



}
