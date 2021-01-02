#pragma once

#include "algorithm.hpp"
#include "conversions.hpp"

#include <vector>
#include <string>
#include <functional>
#include <filesystem>

namespace libimage
{
	using file_path_t = std::filesystem::path;	

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
