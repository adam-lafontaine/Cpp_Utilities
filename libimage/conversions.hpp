#pragma once
#include <cstdint>

namespace libimage
{
	using bits8 = uint8_t;
	using bits32 = uint32_t;

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

}

