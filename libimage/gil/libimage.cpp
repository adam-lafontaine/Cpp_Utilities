#include "libimage.hpp"



namespace libimage
{

	
	


	//======= READING IMAGES =====================


	
	static png_image_t read_image_png(std::string const& img_path)
	{
		//gil::image_read_settings<gil::png_tag> read_settings;
		png_image_t src_img;
		gil::read_image(img_path, src_img, /*read_settings*/gil::png_tag());

		return src_img;
	}
	
	
	static jpeg_image_t read_image_jpeg(std::string const& img_path)
	{
		gil::image_read_settings<gil::jpeg_tag> read_settings;
		jpeg_image_t src_img;
		gil::read_image(img_path, src_img, read_settings);

		return src_img;
	}


	// choose png or jpeg	
	image_t read_image_from_file(file_path_t const& img_path)
	{
		return read_image_png(img_path.string());
	}



	//====== MAKE VIEWS ====================


	view_t make_view(image_t& img)
	{
		return gil::view(img);
	}


	// returns a resized image view
	view_t make_resized_view(image_t& img_src, image_t& img_dst)
	{
		const auto& view = gil::view(img_dst);

		gil::resize_view(gil::const_view(img_src), view, gil::bilinear_sampler());
		return view;
	}


	view_t sub_view(view_t const& view, pixel_range_t const& range) // image_view_factory.hpp
	{
		auto width = range.x_end - range.x_begin;
		auto height = range.y_end - range.y_begin;

		return view_t(width, height, view.xy_at(range.x_begin, range.y_begin));
	}


	view_t column_view(view_t const& view, size_t x)
	{
		return gil::subimage_view(view, x, 0, 1, view.height());
	}


	view_t row_view(view_t const& view, size_t y)
	{
		return gil::subimage_view(view, 0, y, view.width(), 1);
	}


	view_t column_view(view_t const& view, index_t y_begin, index_t y_end, index_t x)
	{
		auto pixel_count = y_end - y_begin;
		return gil::subimage_view(view, x, y_begin, 1, pixel_count);
	}


	view_t row_view(view_t const& view, index_t x_begin, index_t x_end, index_t y)
	{
		auto pixel_count = x_end - x_begin;
		return gil::subimage_view(view, x_begin, y, pixel_count, 1);
	}


	//======= WRITE IMAGES =====================

	
	static void write_image_view_png(std::string const& file_path, view_t const& view)
	{
		gil::write_view(file_path, view, gil::png_tag());
	}

	
	//static void write_image_view_jpeg(std::string const& file_path, view_t const& view)
	//{
	//	gil::jpeg_write_view(file_path, view);

	//	//gil::write_view(file_path, view, gil::jpeg_tag());
	//}


	// choose jpeg or png	
	void write_image_view(file_path_t const& file_path, view_t const& view)
	{
		write_image_view_png(file_path.string(), view);
	}



	//======= CONVERSION FUNCTIONS ==============	


	


	/*rgb_list_t to_rgb_column(view_t const& img_v, index_t y_begin, index_t y_end, index_t x)
	{
		rgb_list_t list;
		list.reserve(y_end - y_begin);

		for (index_t y = y_begin; y < y_end; ++y)
		{
			auto ptr = img_v.row_begin(y);
			list.push_back(to_rgb(ptr[x]));
		}

		return list;
	}


	rgb_list_t to_rgb_column(view_t const& img_v, index_t x)
	{
		return to_rgb_column(img_v, 0, img_v.height(), x);
	}


	rgb_list_t to_rgb_row(view_t const& img_v, index_t x_begin, index_t x_end, index_t y)
	{
		rgb_list_t list;
		list.reserve(x_end - x_begin);

		auto ptr = img_v.row_begin(y);

		for (index_t x = x_begin; x < x_end; ++x)
		{
			list.push_back(to_rgb(ptr[x]));
		}

		return list;
	}


	rgb_list_t to_rgb_row(view_t const& img_v, index_t y)
	{
		return to_rgb_row(img_v, 0, img_v.width(), y);
	}*/


	namespace gray
	{
		

		image_t read_image_from_file(file_path_t const& img_path)
		{
			image_t image;
			gil::read_and_convert_image(img_path.string(), image, gil::png_tag());

			return image;
		}


		static void write_image_view_png(std::string const& file_path, view_t const& view)
		{
			gil::write_view(file_path, view, gil::png_tag());
		}


		//static void write_image_view_jpeg(std::string const& file_path, view_t const& view)
		//{
		//	gil::jpeg_write_view(file_path, view);

		//	//gil::write_view(file_path, view, gil::jpeg_tag());
		//}


		hist_t make_histogram(view_t const& view)
		{
			hist_t hist = { 0 };

			const auto update_hist = [&](auto const& p) { ++hist[p]; };

			gil::for_each_pixel(view, update_hist);

			return hist;
		}
	}


	//======= GRAYSCALE OVERLOADS ================

	gray::view_t make_view(gray::image_t& img)
	{
		return gil::view(img);
	}	


	gray::view_t make_resized_view(gray::image_t& img_src, gray::image_t& img_dst)
	{
		gil::resize_view(gil::const_view(img_src), gil::view(img_dst), gil::bilinear_sampler());

		return gil::view(img_dst);
	}


	gray::view_t sub_view(gray::view_t const& view, pixel_range_t const& range)
	{
		auto width = range.x_end - range.x_begin;
		auto height = range.y_end - range.y_begin;

		return gray::view_t(width, height, view.xy_at(range.x_begin, range.y_begin));
	}


	gray::view_t column_view(gray::view_t const& view, size_t x)
	{
		return gil::subimage_view(view, x, 0, 1, view.height());
	}


	gray::view_t row_view(gray::view_t const& view, size_t y)
	{
		return gil::subimage_view(view, 0, y, view.width(), 1);
	}


	gray::view_t column_view(gray::view_t const& view, index_t y_begin, index_t y_end, index_t x)
	{
		auto pixel_count = y_end - y_begin;
		return gil::subimage_view(view, x, y_begin, 1, pixel_count);
	}


	gray::view_t row_view(gray::view_t const& view, index_t x_begin, index_t x_end, index_t y)
	{
		auto pixel_count = x_end - x_begin;
		return gil::subimage_view(view, x_begin, y, pixel_count, 1);
	}


	void write_image_view(file_path_t const& file_path, gray::view_t const& view)
	{
		gray::write_image_view_png(file_path.string(), view);
	}

}