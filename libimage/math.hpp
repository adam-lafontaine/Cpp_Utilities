#pragma once

#include "boost_gil.hpp"

#include <array>


namespace libimage
{
	constexpr size_t N_HIST_BUCKETS = 16;

	using hist_t = std::array<unsigned, N_HIST_BUCKETS>;
	using hist_full_t = std::array<unsigned, CHANNEL_SIZE>;
	//using hist_16_t = std::array<unsigned, 16>;


	typedef struct RGBHist
	{
		hist_t r = { 0 };
		hist_t g = { 0 };
		hist_t b = { 0 };
	} rgb_hist_t;


	typedef struct
	{
		double mean;
		double sigma;
	} stats_t;


	typedef struct RBGStats
	{
		stats_t r;
		stats_t g;
		stats_t b;
	} rgb_stats_t;

	

	rgb_hist_t make_histograms(view_t const& view);	

	rgb_stats_t make_stats(view_t const& view);

	rgb_stats_t make_stats(view_t const& view, pixel_range_t const& range);

	hist_t make_histogram(gray::view_t const& view);

	stats_t make_stats(gray::view_t const& view);

	stats_t make_stats(gray::view_t const& view, pixel_range_t const& range);
}