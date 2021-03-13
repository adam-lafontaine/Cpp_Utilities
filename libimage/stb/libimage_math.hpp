#pragma once

#include "image_view.hpp"

#include <array>
#include <algorithm>

using r32 = float;


namespace libimage_stb
{
	constexpr size_t CHANNEL_SIZE = 256; // 8 bit channel
	constexpr size_t N_HIST_BUCKETS = 16;

	using hist_t = std::array<u32, N_HIST_BUCKETS>;


	typedef struct channel_stats_t
	{
		r32 mean;
		r32 std_dev;
		hist_t hist;

	} stats_t;


	typedef union rgb_channel_stats_t
	{
		struct
		{
			stats_t red;
			stats_t green;
			stats_t blue;
		};

		stats_t stats[3];

	} rgb_stats_t;


	inline rgb_stats_t calc_stats(view_t const& view)
	{
		u32 const R = 0;
		u32 const G = 1;
		u32 const B = 2;
		constexpr size_t n_channels = 3;

		auto const divisor = CHANNEL_SIZE / N_HIST_BUCKETS;

		std::array<hist_t, n_channels> c_hists = { 0 };
		std::array<r32, n_channels> c_counts = { 0 };

		auto const update = [&](pixel_t const& p) 
		{
			for (u32 c = 0; c < n_channels; ++c)
			{
				auto bucket = p.channels[c] / divisor;

				++c_hists[c][bucket];
				c_counts[c] += bucket;
			}
		};

		std::for_each(view.cbegin(), view.cend(), update);

		auto num_pixels = static_cast<size_t>(view.width) * view.height;

		auto c_means = c_counts;
		for (u32 c = 0; c < n_channels; ++c)
		{
			c_means[c] /= num_pixels;
		}

		std::array<r32, n_channels> c_diff_sq_totals = { 0 };
		std::array<size_t, n_channels> c_qty_totals = { 0 };

		for (u32 bucket = 0; bucket < c_hists[0].size(); ++bucket)
		{
			for (u32 c = 0; c < n_channels; ++c)
			{
				auto qty = c_hists[c][bucket];

				if (!qty)
					continue;

				c_qty_totals[c] += qty;
				r32 diff = static_cast<r32>(bucket) - c_means[c];

				c_diff_sq_totals[c] += qty * diff * diff;
			}
		}

		rgb_stats_t rgb_stats;

		for (u32 c = 0; c < n_channels; ++c)
		{
			r32 std_dev = c_qty_totals[c] == 0 ? 0.0f : sqrtf(c_diff_sq_totals[c] / c_qty_totals[c]);
			rgb_stats.stats[0] = { c_means[c], std_dev, c_hists[c] };
		}

		return rgb_stats;
	}


	inline stats_t calc_stats(gray::view_t const& view)
	{
		hist_t hist = { 0 };
		r32 count = 0.0f;

		auto const divisor = CHANNEL_SIZE / N_HIST_BUCKETS;

		auto const update = [&](gray::pixel_t const& shade)
		{
			auto bucket = shade / divisor;
			++hist[bucket];
			count += bucket;
		};

		std::for_each(view.cbegin(), view.cend(), update);

		auto num_pixels = static_cast<size_t>(view.width) * view.height;

		auto mean = count / num_pixels;
		assert(mean >= 0 && mean <= hist.size());

		r32 diff_sq_total = 0.0f;
		size_t qty_total = 0;
		for (u32 bucket = 0; bucket < hist.size(); ++bucket)
		{
			auto qty = hist[bucket];

			if (!qty)
				continue;

			qty_total += qty;
			r32 diff = static_cast<r32>(bucket) - mean;

			diff_sq_total += qty * diff * diff;
		}

		r32 std_dev = qty_total == 0 ? 0.0f : sqrtf(diff_sq_total / qty_total);

		return { mean, std_dev, hist };
	}
}