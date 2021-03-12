#pragma once

#include "libimage_stb.hpp"

#include <filesystem>

namespace fs = std::filesystem;

namespace libimage_stb
{
	inline image_t read_image_from_file(fs::path const& img_path)
	{
		auto file_path_str = img_path.string();

		return read_image_from_file(file_path_str.c_str());
	}


	inline void write_image(fs::path const& file_path, image_t const& image)
	{
		auto file_path_str = file_path.string();

		write_image(file_path_str.c_str(), image);
	}


	inline void write_view(fs::path const& file_path, view_t const& view)
	{
		auto file_path_str = file_path.string();

		write_view(file_path_str.c_str(), view);
	}


	namespace gray
	{
		inline image_t read_image_from_file(fs::path const& img_path)
		{
			auto file_path_str = img_path.string();

			return read_image_from_file(file_path_str.c_str());
		}
	}


	inline void write_image(fs::path const& file_path, gray::image_t const& image)
	{
		auto file_path_str = file_path.string();

		write_image(file_path_str.c_str(), image);
	}


	inline void write_view(fs::path const& file_path, gray::view_t const& view)
	{
		auto file_path_str = file_path.string();

		write_view(file_path_str.c_str(), view);
	}
}