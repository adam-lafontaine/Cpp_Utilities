#include "libimage_math.hpp"
#include "libimage_stb.hpp"

#include <numeric>


namespace libimage_stb
{
	rgb_stats_t calc_stats(view_t const& view)
	{
		constexpr auto n_channels = RGBA_CHANNELS - 1;

		auto const divisor = CHANNEL_SIZE / N_HIST_BUCKETS;

		std::array<hist_t, n_channels> c_hists = { 0 };
		std::array<r32, n_channels> c_counts = { 0 };

		auto const update = [&](pixel_t const& p)
		{
			for (u32 c = 0; c < n_channels; ++c)
			{
				auto bucket = p.channels[c] / divisor;

				++c_hists[c][bucket];
				c_counts[c] += p.channels[c];
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
			rgb_stats.stats[c] = { c_means[c], std_dev, c_hists[c] };
		}

		return rgb_stats;
	}


	stats_t calc_stats(gray::view_t const& view)
	{
		hist_t hist = { 0 };
		r32 count = 0.0f;

		auto const divisor = CHANNEL_SIZE / N_HIST_BUCKETS;

		auto const update = [&](gray::pixel_t const& shade)
		{
			auto bucket = shade / divisor;
			++hist[bucket];
			count += shade;
		};

		std::for_each(view.cbegin(), view.cend(), update);

		auto num_pixels = static_cast<size_t>(view.width) * view.height;

		auto mean = count / num_pixels;
		assert(mean >= 0);
		assert(mean < CHANNEL_SIZE);

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


	void draw_histogram(hist_t const& hist, gray::image_t& image_dst)
	{
		assert(!image_dst.width);
		assert(!image_dst.height);
		assert(!image_dst.data);
		assert(N_HIST_BUCKETS < CHANNEL_SIZE);
		assert(hist.size() == N_HIST_BUCKETS);

		u32 const max_relative_qty = 200;
		u32 const image_height = max_relative_qty + 1;

		u8 const n_buckets = static_cast<u8>(N_HIST_BUCKETS);	

		u32 const bucket_width = 20;
		u32 const bucket_spacing = 1;
		u32 const image_width = n_buckets * (bucket_spacing + bucket_width) + bucket_spacing;

		make_image(image_dst, image_width, image_height);
		std::fill(image_dst.begin(), image_dst.end(), 255);

		auto max = std::accumulate(hist.begin(), hist.end(), (r32)0);

		const auto norm = [&](u32 count)
		{
			return max_relative_qty - static_cast<u32>(count / max * max_relative_qty);
		};		

		pixel_range_t bar_range;
		bar_range.x_begin = bucket_spacing;
		bar_range.x_end = (bucket_spacing + bucket_width);
		bar_range.y_begin = 0;
		bar_range.y_end = image_height;

		pixel_range_t cap_range;
		cap_range.x_begin = bar_range.x_begin;
		cap_range.x_end = bar_range.x_end;
		cap_range.y_begin = 0;
		cap_range.y_end = 0;

		for (u8 bucket = 0; bucket < n_buckets; ++bucket)
		{
			cap_range.y_begin = norm(hist[bucket]);
			cap_range.y_end = cap_range.y_begin + 1;
			bar_range.y_begin = cap_range.y_end;

			auto cap_view = sub_view(image_dst, cap_range);
			std::fill(cap_view.begin(), cap_view.end(), 0);

			if (bar_range.y_end > bar_range.y_begin)
			{
				u8 shade = n_buckets * (bucket + 1) - 1;
				auto bar_view = sub_view(image_dst, bar_range);
				std::fill(bar_view.begin(), bar_view.end(), shade);
			}

			bar_range.x_begin += (bucket_spacing + bucket_width);
			bar_range.x_end += (bucket_spacing + bucket_width);
			cap_range.x_begin += (bucket_spacing + bucket_width);
			cap_range.x_end += (bucket_spacing + bucket_width);
		}

	}


	void draw_histogram(rgb_stats_t const& rgb_stats, image_t& image_dst)
	{
		assert(!image_dst.width);
		assert(!image_dst.height);
		assert(!image_dst.data);
		assert(N_HIST_BUCKETS < CHANNEL_SIZE);

		constexpr auto n_channels = RGBA_CHANNELS - 1;

		u32 const max_relative_qty = 200;
		u32 const image_height = max_relative_qty + 1;

		u8 const n_buckets = static_cast<u8>(N_HIST_BUCKETS);

		u32 const c_bucket_width = 10;
		u32 const c_bucket_spacing = 1;
		u32 const bucket_width = n_channels * (c_bucket_width + c_bucket_spacing);
		u32 const bucket_spacing = 3;
		u32 const image_width = n_buckets * (bucket_spacing + bucket_width) + bucket_spacing;

		pixel_t white = to_pixel(255, 255, 255);
		pixel_t black = to_pixel(0, 0, 0);

		make_image(image_dst, image_width, image_height);
		std::fill(image_dst.begin(), image_dst.end(), white);

		for (u32 c = 0; c < n_channels; ++c)
		{
			auto& hist = rgb_stats.stats[c].hist;

			auto max = std::accumulate(hist.begin(), hist.end(), (r32)0);

			const auto norm = [&](u32 count)
			{
				return max_relative_qty - static_cast<u32>(count / max * max_relative_qty);
			};

			pixel_range_t bar_range;
			bar_range.x_begin = bucket_spacing + c * (c_bucket_width + c_bucket_spacing);
			bar_range.x_end = bar_range.x_begin + c_bucket_width;
			bar_range.y_begin = 0;
			bar_range.y_end = image_height;

			pixel_range_t cap_range;
			cap_range.x_begin = bar_range.x_begin;
			cap_range.x_end = bar_range.x_end;
			cap_range.y_begin = 0;
			cap_range.y_end = 0;

			for (u8 bucket = 0; bucket < n_buckets; ++bucket)
			{
				cap_range.y_begin = norm(hist[bucket]);
				cap_range.y_end = cap_range.y_begin + 1;
				bar_range.y_begin = cap_range.y_end;

				auto cap_view = sub_view(image_dst, cap_range);
				std::fill(cap_view.begin(), cap_view.end(), black);

				if (bar_range.y_end > bar_range.y_begin)
				{
					u8 shade = n_buckets * (bucket + 1) - 1;
					pixel_t color = to_pixel(0, 0, 0, 255);
					color.channels[c] = shade;
					auto bar_view = sub_view(image_dst, bar_range);
					std::fill(bar_view.begin(), bar_view.end(), color);
				}

				bar_range.x_begin += (bucket_spacing + bucket_width);
				bar_range.x_end += (bucket_spacing + bucket_width);
				cap_range.x_begin += (bucket_spacing + bucket_width);
				cap_range.x_end += (bucket_spacing + bucket_width);
			}
		}

	}
}