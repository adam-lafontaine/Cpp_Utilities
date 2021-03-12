#include "libimage_stb.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <algorithm>
#include <execution>
#include <filesystem>

namespace fs = std::filesystem;

namespace libimage_stb
{
	image_t read_image_from_file(const char* img_path)
	{
		int width = 0;
		int height = 0;
		int image_channels = 0;
		int desired_channels = 4;

		auto data = (rgba_pixel*)stbi_load(img_path, &width, &height, &image_channels, desired_channels);

		image_t image(width, height);
		image.data = data;

		return image;
	}


	view_t make_view(image_t& img)
	{
		view_t view;

		view.image_data = img.data;
		view.image_width = img.width;
		view.x_begin = 0;
		view.y_begin = 0;
		view.x_end = img.width;
		view.y_end = img.height;
		view.width = img.width;
		view.height = img.height;

		return view;
	}


	view_t sub_view(image_t& image, pixel_range_t const& range)
	{
		view_t sub_view;

		sub_view.image_data = image.data;
		sub_view.image_width = image.width;
		sub_view.x_begin = range.x_begin;
		sub_view.y_begin = range.y_begin;
		sub_view.x_end = range.x_end;
		sub_view.y_end = range.y_end;
		sub_view.width = range.x_end - range.x_begin;
		sub_view.height = range.y_end - range.y_begin;

		return sub_view;
	}


	view_t sub_view(view_t const& view, pixel_range_t const& range)
	{
		view_t sub_view;

		sub_view.image_data = view.image_data;
		sub_view.image_width = view.image_width;
		sub_view.x_begin = view.x_begin + range.x_begin;
		sub_view.y_begin = view.y_begin + range.y_begin;
		sub_view.x_end = view.x_end + range.x_end;
		sub_view.y_end = view.y_end + range.y_end;
		sub_view.width = range.x_end - range.x_begin;
		sub_view.height = range.y_end - range.y_begin;

		return sub_view;
	}


	view_t row_view(image_t& image, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = image.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(image, range);
	}


	view_t row_view(view_t& view, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = view.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(view, range);
	}


	view_t column_view(image_t& image, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = image.height;

		return sub_view(image, range);
	}


	view_t column_view(view_t& view, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = view.height;

		return sub_view(view, range);
	}


	namespace gray
	{
		image_t read_image_from_file(const char* img_path)
		{
			int width = 0;
			int height = 0;
			int image_channels = 0;
			int desired_channels = 1;

			auto data = (pixel_t*)stbi_load(img_path, &width, &height, &image_channels, desired_channels);

			image_t image(width, height);
			image.data = data;

			return image;
		}
	}


	//======= GRAYSCALE OVERLOADS ==================


	gray::view_t make_view(gray::image_t& img)
	{
		gray::view_t view;

		view.image_data = img.data;
		view.image_width = img.width;
		view.x_begin = 0;
		view.y_begin = 0;
		view.x_end = img.width;
		view.y_end = img.height;
		view.width = img.width;
		view.height = img.height;

		return view;
	}


	gray::view_t sub_view(gray::image_t& image, pixel_range_t const& range)
	{
		gray::view_t sub_view;

		sub_view.image_data = image.data;
		sub_view.image_width = image.width;
		sub_view.x_begin = range.x_begin;
		sub_view.y_begin = range.y_begin;
		sub_view.x_end = range.x_end;
		sub_view.y_end = range.y_end;
		sub_view.width = range.x_end - range.x_begin;
		sub_view.height = range.y_end - range.y_begin;

		return sub_view;
	}


	gray::view_t sub_view(gray::view_t const& view, pixel_range_t const& range)
	{
		gray::view_t sub_view;

		sub_view.image_data = view.image_data;
		sub_view.image_width = view.image_width;
		sub_view.x_begin = view.x_begin + range.x_begin;
		sub_view.y_begin = view.y_begin + range.y_begin;
		sub_view.x_end = view.x_end + range.x_end;
		sub_view.y_end = view.y_end + range.y_end;
		sub_view.width = range.x_end - range.x_begin;
		sub_view.height = range.y_end - range.y_begin;

		return sub_view;
	}


	gray::view_t row_view(gray::image_t& image, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = image.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(image, range);
	}


	gray::view_t row_view(gray::view_t& view, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = view.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(view, range);
	}


	gray::view_t column_view(gray::image_t& image, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = image.height;

		return sub_view(image, range);
	}


	gray::view_t column_view(gray::view_t& view, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = view.height;

		return sub_view(view, range);
	}


	void write_image(const char* file_path, image_t const& image)
	{
		int width = static_cast<int>(image.width);
		int height = static_cast<int>(image.height);
		int channels = static_cast<int>(RGBA_CHANNELS);
		auto const data = image.data;

		auto ext = fs::path(file_path).extension();

		if (ext == ".bmp" || ext == ".BMP")
		{
			stbi_write_bmp(file_path, width, height, channels, data);
		}
		else if (ext == ".png" || ext == ".PNG")
		{
			int stride_in_bytes = width * channels;

			stbi_write_png(file_path, width, height, channels, data, stride_in_bytes);
		}
		else if (ext == ".jpg" || ext == ".jpeg" || ext == ".JPG" || ext == ".JPEG")
		{
			// TODO: quality?
			// stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
		}
	}


	static image_t make_image(view_t const& view)
	{
		image_t image(view.width, view.height);

		image.data = (pixel_t*)malloc(sizeof(pixel_t) * view.width * view.height);
		std::transform(view.cbegin(), view.cend(), image.begin(), [](auto p) { return p; });		

		return image;
	}


	void write_view(const char* file_path, view_t const& view)
	{
		auto image = make_image(view);

		write_image(file_path, image);
	}
}


