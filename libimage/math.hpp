#pragma once

#include "boost_gil.hpp"

namespace libimage
{
	using hist_t = std::array<unsigned, CHANNEL_SIZE>;

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

	hist_t make_histogram(gray::view_t const& view);

	rgb_hist_t make_histograms(view_t const& view);

	stats_t make_stats(gray::view_t const& view);

	rgb_stats_t make_stats(view_t const& view);
}