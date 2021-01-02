#pragma once

#include "algorithm.hpp"
#include "conversions.hpp"
#include "math.hpp"

#include <vector>
#include <string>
#include <functional>
#include <filesystem>

namespace libimage
{
	using file_path_t = std::filesystem::path;	

	
	constexpr auto IMAGE_FILE_EXTENSION = ".png";


	

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
