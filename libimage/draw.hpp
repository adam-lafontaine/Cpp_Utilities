#pragma once

#include <filesystem>

namespace draw
{
	using file_path_t = std::filesystem::path;

	void histogram(file_path_t const& img_src, file_path_t const& hist_dst);
}