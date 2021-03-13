#include "libimage_stb.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include <algorithm>
#include <execution>
#include <filesystem>

namespace fs = std::filesystem;

namespace libimage_stb
{
	void read_image_from_file(const char* img_path_src, image_t& image_dst)
	{
		int width = 0;
		int height = 0;
		int image_channels = 0;
		int desired_channels = 4;

		auto data = (rgba_pixel*)stbi_load(img_path_src, &width, &height, &image_channels, desired_channels);

		image_dst.data = data;
		image_dst.width = width;
		image_dst.height = height;
	}


	view_t make_view(image_t const& img)
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


	view_t sub_view(image_t const& image, pixel_range_t const& range)
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


	view_t row_view(image_t const& image, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = image.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(image, range);
	}


	view_t row_view(view_t const& view, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = view.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(view, range);
	}


	view_t column_view(image_t const& image, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = image.height;

		return sub_view(image, range);
	}


	view_t column_view(view_t const& view, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = view.height;

		return sub_view(view, range);
	}


	void write_image(image_t const& image_src, const char* file_path_dst)
	{
		int width = static_cast<int>(image_src.width);
		int height = static_cast<int>(image_src.height);
		int channels = static_cast<int>(RGBA_CHANNELS);
		auto const data = image_src.data;

		auto ext = fs::path(file_path_dst).extension();

		if (ext == ".bmp" || ext == ".BMP")
		{
			stbi_write_bmp(file_path_dst, width, height, channels, data);
		}
		else if (ext == ".png" || ext == ".PNG")
		{
			int stride_in_bytes = width * channels;

			stbi_write_png(file_path_dst, width, height, channels, data, stride_in_bytes);
		}
		else if (ext == ".jpg" || ext == ".jpeg" || ext == ".JPG" || ext == ".JPEG")
		{
			// TODO: quality?
			// stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
		}
	}


	static void make_image(view_t const& view, image_t& image_dst)
	{
		image_dst.width = view.width;
		image_dst.height = view.height;
		image_dst.data = (pixel_t*)malloc(sizeof(pixel_t) * view.width * view.height);
		std::transform(view.cbegin(), view.cend(), image_dst.begin(), [](auto p) { return p; });

		/*auto p = img_dst.begin();
		for (auto it = view.cbegin(); it != view.cend(); ++it)
		{
			auto img = *p;
			auto v = *it;
			*p++ = *it;
		}*/
	}


	void write_view(view_t const& view_src, const char* file_path_dst)
	{
		image_t image;
		make_image(view_src, image);

		write_image(image, file_path_dst);
	}


	void resize_image(image_t const& image_src, image_t& image_dst)
	{
		int channels = static_cast<int>(RGBA_CHANNELS);

		int width_src = static_cast<int>(image_src.width);
		int height_src = static_cast<int>(image_src.height);		
		int stride_bytes_src = width_src * channels;

		int width_dst = static_cast<int>(image_dst.width);
		int height_dst = static_cast<int>(image_dst.height);
		int stride_bytes_dst = width_dst * channels;

		image_dst.data = (pixel_t*)malloc(sizeof(pixel_t) * image_dst.width * image_dst.height);

		stbir_resize_uint8(
			(u8*)image_src.data, width_src, height_src, stride_bytes_src,
			(u8*)image_dst.data, width_dst, height_dst, stride_bytes_dst,
			channels);
	}


	view_t make_resized_view(image_t const& img_src, image_t& img_dst)
	{
		resize_image(img_src, img_dst);

		return make_view(img_dst);
	}


	namespace gray
	{
		void read_image_from_file(const char* file_path_src, image_t& image_dst)
		{
			int width = 0;
			int height = 0;
			int image_channels = 0;
			int desired_channels = 1;

			auto data = (pixel_t*)stbi_load(file_path_src, &width, &height, &image_channels, desired_channels);

			image_dst.data = data;
			image_dst.width = width;
			image_dst.height = height;
		}
	}


	//======= GRAYSCALE OVERLOADS ==================


	gray::view_t make_view(gray::image_t const& img)
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


	gray::view_t sub_view(gray::image_t const& image, pixel_range_t const& range)
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


	gray::view_t row_view(gray::image_t const& image, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = image.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(image, range);
	}


	gray::view_t row_view(gray::view_t const& view, u32 y)
	{
		pixel_range_t range;
		range.x_begin = 0;
		range.x_end = view.width;
		range.y_begin = y;
		range.y_end = y;

		return sub_view(view, range);
	}


	gray::view_t column_view(gray::image_t const& image, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = image.height;

		return sub_view(image, range);
	}


	gray::view_t column_view(gray::view_t const& view, u32 x)
	{
		pixel_range_t range;
		range.x_begin = x;
		range.x_end = x;
		range.y_begin = 0;
		range.y_end = view.height;

		return sub_view(view, range);
	}


	void write_image(gray::image_t const& image_src, const char* file_path_dst)
	{
		int width = static_cast<int>(image_src.width);
		int height = static_cast<int>(image_src.height);
		int channels = 1;
		auto const data = image_src.data;

		auto ext = fs::path(file_path_dst).extension();

		if (ext == ".bmp" || ext == ".BMP")
		{
			stbi_write_bmp(file_path_dst, width, height, channels, data);
		}
		else if (ext == ".png" || ext == ".PNG")
		{
			int stride_in_bytes = width * channels;

			stbi_write_png(file_path_dst, width, height, channels, data, stride_in_bytes);
		}
		else if (ext == ".jpg" || ext == ".jpeg" || ext == ".JPG" || ext == ".JPEG")
		{
			// TODO: quality?
			// stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
		}
	}


	static void make_image(gray::view_t const& view_src, gray::image_t image_dst)
	{
		image_dst.width = view_src.width;
		image_dst.height = view_src.height;
		image_dst.data = (gray::pixel_t*)malloc(sizeof(pixel_t) * view_src.width * view_src.height);
		std::transform(view_src.cbegin(), view_src.cend(), image_dst.begin(), [](auto p) { return p; });
	}


	void write_view(gray::view_t const& view_src, const char* file_path_dst)
	{
		gray::image_t image;
		make_image(view_src, image);

		write_image(image, file_path_dst);
	}


	void resize_image(gray::image_t const& image_src, gray::image_t& image_dst)
	{
		int channels = 1;

		int width_src = static_cast<int>(image_src.width);
		int height_src = static_cast<int>(image_src.height);
		int stride_bytes_src = width_src * channels;

		int width_dst = static_cast<int>(image_dst.width);
		int height_dst = static_cast<int>(image_dst.height);
		int stride_bytes_dst = width_dst * channels;

		image_dst.data = (gray::pixel_t*)malloc(sizeof(gray::pixel_t) * image_dst.width * image_dst.height);

		stbir_resize_uint8(
			(u8*)image_src.data, width_src, height_src, stride_bytes_src,
			(u8*)image_dst.data, width_dst, height_dst, stride_bytes_dst,
			channels);
	}


	gray::view_t make_resized_view(gray::image_t const& image_src, gray::image_t& image_dst)
	{
		resize_image(image_src, image_dst);

		return make_view(image_dst);
	}
}


