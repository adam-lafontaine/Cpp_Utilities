#pragma once
#include "boost_gil.hpp"

#include <cstdint>

namespace libimage
{
	constexpr gil::red_t   GIL_RED;
	constexpr gil::green_t GIL_GREEN;
	constexpr gil::blue_t  GIL_BLUE;
	constexpr gil::alpha_t GIL_ALPHA;

	

	typedef struct {
		bits8 r;
		bits8 g;
		bits8 b;
	} rgb_t;


	typedef struct
	{
		bits8 r;
		bits8 g;
		bits8 b;
		bits8 a;
	} rgba_t;


	constexpr bits32 to_bits32(bits8 red, bits8 green, bits8 blue) // TODO: to_bits24
	{
		const bits32 r = red;
		const bits32 g = green;
		const bits32 b = blue;

		return (r << 16) + (g << 8) + b;
	}


	constexpr bits32 to_bits32(bits8 red, bits8 green, bits8 blue, bits8 alpha)
	{
		const bits32 r = red;
		const bits32 g = green;
		const bits32 b = blue;
		const bits32 a = alpha;

		return (r << 24) + (g << 16) + (b << 8) + a;
	}


	constexpr bits32 to_bits32(rgb_t const& rgb) // TODO: to_bits24
	{
		const bits32 r = rgb.r;
		const bits32 g = rgb.g;
		const bits32 b = rgb.b;

		return (r << 16) + (g << 8) + b;
	}


	constexpr bits32 to_bits32(rgba_t const& rgba)
	{
		return to_bits32(rgba.r, rgba.g, rgba.b, rgba.a);
	}


	constexpr rgb_t to_rgb(bits8 red, bits8 green, bits8 blue)
	{
		return { red, green, blue };
	}


	// converts pixel reference to a 32 bit integer
	inline bits32 to_bits32(pixel_t const& src)
	{
		auto const r = gil::get_color(src, GIL_RED);
		auto const g = gil::get_color(src, GIL_GREEN);
		auto const b = gil::get_color(src, GIL_BLUE);
		auto const a = gil::get_color(src, GIL_ALPHA);

		return to_bits32(r, g, b, a);
	}


	// converts pixel reference to a 32 bit integer
	inline bits32 to_bits32(ref_t const& src)
	{
		auto const r = gil::get_color(src, GIL_RED);
		auto const g = gil::get_color(src, GIL_GREEN);
		auto const b = gil::get_color(src, GIL_BLUE);
		auto const a = gil::get_color(src, GIL_ALPHA);

		return to_bits32(r, g, b, a);
	}


	// converts a pointer to a pixel to a 32 bit integer
	inline bits32 to_bits32(pixel_ptr_t const& ptr)
	{
		auto const r = gil::get_color(*ptr, GIL_RED);
		auto const g = gil::get_color(*ptr, GIL_GREEN);
		auto const b = gil::get_color(*ptr, GIL_BLUE);
		auto const a = gil::get_color(*ptr, GIL_ALPHA);

		return to_bits32(r, g, b, a);
	}


	inline rgb_t to_rgb(pixel_t const& pixel)
	{
		return
		{
			static_cast<bits8>(gil::get_color(pixel, GIL_RED)),
			static_cast<bits8>(gil::get_color(pixel, GIL_GREEN)),
			static_cast<bits8>(gil::get_color(pixel, GIL_BLUE))
		};
	}


	inline rgba_t to_rgba(pixel_t const& pixel)
	{
		return
		{
			static_cast<bits8>(gil::get_color(pixel, GIL_RED)),
			static_cast<bits8>(gil::get_color(pixel, GIL_GREEN)),
			static_cast<bits8>(gil::get_color(pixel, GIL_BLUE)),
			static_cast<bits8>(gil::get_color(pixel, GIL_ALPHA))
		};
	}


	inline pixel_t to_pixel(bits8 r, bits8 g, bits8 b, bits8 a = 255)
	{
		return pixel_t(r, g, b, a); // png
		// return pixel_t(r, g, b); // jpeg
	}


	// creates a pixel object from color values
	inline pixel_t to_pixel(rgb_t const& rgb)
	{
		return to_pixel(rgb.r, rgb.g, rgb.b);
	}


	inline pixel_t to_pixel(rgba_t const& rgba)
	{
		return to_pixel(rgba.r, rgba.g, rgba.b, rgba.a);
	}

}

