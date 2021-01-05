#include "draw.hpp"
#include "libimage.hpp"

#include <algorithm>
#include <array>

namespace draw
{
	namespace img = libimage;


	static void normalize(img::rgb_hist_t& hist, unsigned max_qty)
	{
		const auto find_max = [](auto const& list)
		{
			auto it = std::max_element(list.begin(), list.end());
			return *it;
		};

		double const max = find_max(std::array<unsigned, 3>{ find_max(hist.r), find_max(hist.g), find_max(hist.b) });

		const auto norm = [&](unsigned count)
		{
			return static_cast<unsigned>(count / max * max_qty);
		};

		for (size_t i = 0; i < hist.r.size(); ++i)
		{
			hist.r[i] = norm(hist.r[i]);
			hist.g[i] = norm(hist.g[i]);
			hist.b[i] = norm(hist.b[i]);
		}
	}


	void histogram(file_path_t const& img_src, file_path_t const& hist_dst)
	{
		unsigned const max_relative_qty = 100;

		auto image_src = img::read_image_from_file(img_src);
		auto view_src = img::make_view(image_src);
		auto hist = img::make_histograms(view_src);

		auto const hist_img_width = hist.r.size();
		auto const hist_img_height = max_relative_qty + 1;

		auto image_dst = img::image_t(hist_img_width, hist_img_height);
		auto view_dst = img::make_view(image_dst);

		const auto find_max = [](auto const& list)
		{
			auto it = std::max_element(list.begin(), list.end());
			return *it;
		};

		double const max = find_max(std::array<unsigned, 3>{ find_max(hist.r), find_max(hist.g), find_max(hist.b) });

		const auto norm = [&](unsigned count)
		{
			return max_relative_qty - static_cast<unsigned>(count / max * max_relative_qty);
		};

		auto const red = img::to_pixel(img::rgb_t{ 255, 0, 0 });
		auto const green = img::to_pixel(img::rgb_t{ 0, 255, 0 });
		auto const blue = img::to_pixel(img::rgb_t{ 0, 0, 255 });

		for (size_t shade = 0; shade < hist_img_width; ++shade)
		{
			auto y = norm(hist.r[shade]);
			*view_dst.at(shade, y) = red;

			y = norm(hist.g[shade]);
			*view_dst.at(shade, y) = green;

			y = norm(hist.b[shade]);
			*view_dst.at(shade, y) = blue;
		}

		img::write_image_view(hist_dst, view_dst);
	}
}