#pragma once



#include <cstdint>
#include <functional>



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
				free(data);
			}
		}

		rgba_pixel_t* begin() { return data; }
		rgba_pixel_t* end() { return data + (u64)width * (u64)height; }
	};

	using image_t = rgba_image_t;


	class rgba_image_view_t
	{
	public:

		rgba_pixel* image_data = 0;
		u32 image_width = 0;

		u32 x_begin = 0;
		u32 x_end = 0;
		u32 y_begin = 0;
		u32 y_end = 0;

		u32 width = 0;
		u32 height = 0;

		pixel_t* row_begin(u32 y) const
		{
			auto offset = (y_begin + y) * image_width + x_begin;
			return image_data + (u64)offset;
		}

		pixel_t* xy_at(u32 x, u32 y) const
		{
			return row_begin(y) + x;
		}

	};

	using view_t = rgba_image_view_t;


	typedef struct
	{
		u32 x_begin;
		u32 x_end;
		u32 y_begin;
		u32 y_end;

	} pixel_range_t;


	image_t read_image_from_file(const char* img_path);

	view_t make_view(image_t& img);

	view_t sub_view(image_t& image, pixel_range_t const& range);

	view_t sub_view(view_t const& view, pixel_range_t const& range);

	view_t row_view(image_t& image, u32 y);

	view_t row_view(view_t& view, u32 y);


	using fe_func_t = std::function<void(pixel_t& p)>;

	namespace seq
	{
		void for_each_pixel(image_t& image, fe_func_t const& func);

		void for_each_pixel(view_t& view, fe_func_t const& func);
	}


	namespace par
	{
		void for_each_pixel(image_t& image, fe_func_t const& func);

		void for_each_pixel(view_t& view, fe_func_t const& func);
	}


}