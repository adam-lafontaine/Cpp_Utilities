#include "math.hpp"
#include "algorithm.hpp"
#include "conversions.hpp"

#include <cassert>

namespace libimage
{
	rgb_hist_t make_histograms(view_t const& view)
	{
		rgb_hist_t hist;
		auto const update_hist = [&](pixel_t const& p) 
		{
			auto const rgb = to_rgb(p);
			++(hist.r[rgb.r]);
			++(hist.g[rgb.g]);
			++(hist.b[rgb.b]);
		};

		seq::for_each_pixel(view, update_hist);

		return hist;
	}


	rgb_stats_t make_stats(view_t const& view)
	{
		typedef struct Props
		{
			hist_t hist = { 0 };
			double count = 0;
			double mean = 0;
			double diff_sq_total = 0;
			double sigma = 0;
		} props_t;

		size_t R = 0;
		size_t G = 1;
		size_t B = 2;

		std::array<props_t, 3> props = { 0 };

		auto const update = [&](pixel_t const& p)
		{
			auto const rgb = to_rgb(p);

			++(props[R].hist[rgb.r]);
			++(props[G].hist[rgb.g]);
			++(props[B].hist[rgb.b]);

			props[R].count += rgb.r;
			props[G].count += rgb.g;
			props[B].count += rgb.b;
		};

		seq::for_each_pixel(view, update);

		auto num_pixels = static_cast<size_t>(view.width() * view.height());

		for (auto& prop : props)
			prop.mean = prop.count / num_pixels;


		auto const diff_sq_update = [](props_t& prop, size_t shade)
		{
			auto val = shade;
			auto qty = prop.hist[shade];

			if (!qty)
				return;

			double diff = val - prop.mean;

			prop.diff_sq_total += qty * diff * diff;
		};

		for (size_t shade = 0; shade < CHANNEL_SIZE; ++shade)
		{
			for (auto& prop : props)
				diff_sq_update(prop, shade);
		}

		for (auto& prop : props)
			prop.sigma = std::sqrt(prop.diff_sq_total / num_pixels);

		
		return {
			{ props[R].mean, props[R].sigma },
			{ props[G].mean, props[G].sigma },
			{ props[B].mean, props[B].sigma },
		};

	}


	rgb_stats_t make_stats(view_t const& view, pixel_range_t const& range)
	{
		auto width = range.x_end - range.x_begin;
		auto height = range.y_end - range.y_begin;

		auto sub = view_t(width, height, view.xy_at(range.x_begin, range.y_begin));

		return make_stats(sub);
	}


	static double sigma(hist_t const& hist, double mean)
	{
		double diff_sq_total = 0;
		size_t qty_total = 0;

		auto const update = [&](size_t shade)
		{
			auto val = shade;
			auto qty = hist[shade];

			if (!qty)
				return;

			qty_total += qty;
			double diff = val - mean;

			diff_sq_total += qty * diff * diff;
		};

		for (size_t shade = 0; shade < hist.size(); ++shade)
		{
			update(shade);
		}

		return qty_total == 0 ? 0 : std::sqrt(diff_sq_total / qty_total);
	}


	hist_t make_histogram(gray::view_t const& view)
	{
		hist_t hist = { 0 };

		auto const update_hist = [&](gray::pixel_t const& p) { ++hist[p[0]]; };

		seq::for_each_pixel(view, update_hist);

		return hist;
	}


	stats_t make_stats(gray::view_t const& view)
	{
		hist_t hist = { 0 };
		double count = 0;
		auto const update = [&](gray::pixel_t const& p)
		{
			auto shade = p[0];
			++hist[shade];
			count += shade;
		};

		seq::for_each_pixel(view, update);

		auto num_pixels = static_cast<size_t>(view.width() * view.height());

		auto mean = count / num_pixels;
		assert(mean >= 0 && mean <= hist.size());

		return { mean, sigma(hist, mean) };
	}


	stats_t make_stats(gray::view_t const& view, pixel_range_t const& range)
	{
		auto width = range.x_end - range.x_begin;
		auto height = range.y_end - range.y_begin;

		auto sub = gray::view_t(width, height, view.xy_at(range.x_begin, range.y_begin));

		return make_stats(sub);
	}
}