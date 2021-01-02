#include "../../libimage/libimage.hpp"

#include <iostream>

namespace fs = std::filesystem;
namespace img = libimage;

constexpr auto SRC_IMAGE_PATH = "D:/repos/Cpp_Utilities/CppUtilTests/LibImage/in_files/png/cadillac.png";
constexpr auto DST_IMAGE_ROOT = "D:/repos/Cpp_Utilities/CppUtilTests/LibImage/out_files";


void empty_dir(fs::path const& dir);
void print(img::view_t const& view);
void print(img::gray::view_t const& view);


int main()
{
	auto dst_root = fs::path(DST_IMAGE_ROOT);
	empty_dir(dst_root);

	auto image = img::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view = img::make_view(image);
	print(view);

	auto w = view.width();
	auto h = view.height();	

	auto resized_image = img::image_t(h, w);
	auto resized_view = img::make_resized_view(image, resized_image);
	print(resized_view);
	img::write_image_view(dst_root / "resized.png", resized_view);

	img::pixel_range_t range = { w * 1/3, w * 2/3, h * 1/3, h * 2/3 };
	auto sub_view = img::sub_view(view, range);
	print(sub_view);
	img::write_image_view(dst_root / "sub.png", sub_view);

	auto row_view = img::row_view(view, 2);
	print(row_view);

	auto col_view = img::column_view(view, 2);
	print(col_view);


	auto image_gray = img::gray::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view_gray = img::make_view(image_gray);
	print(view_gray);

	w = view_gray.width();
	h = view_gray.height();

	auto resized_image_gray = img::gray::image_t(h, w);
	auto resized_view_gray = img::make_resized_view(image_gray, resized_image_gray);
	print(resized_view_gray);
	img::write_image_view(dst_root / "resized_gray.png", resized_view_gray);

	auto sub_view_gray = img::sub_view(view_gray, range);
	print(sub_view_gray);
	img::write_image_view(dst_root / "sub_gray.png", sub_view_gray);

	auto row_view_gray = img::row_view(view, 2);
	print(row_view_gray);

	auto col_view_gray = img::column_view(view, 2);
	print(col_view_gray);
}


void empty_dir(fs::path const& dir)
{
	for (auto const& entry : fs::directory_iterator(dir))
	{
		fs::remove_all(entry);
	}
}


void print(img::view_t const& view)
{
	auto w = view.width();
	auto h = view.height();

	std::cout << "width: " << w << " height: " << h << "\n";
}


void print(img::gray::view_t const& view)
{
	auto w = view.width();
	auto h = view.height();

	std::cout << "width: " << w << " height: " << h << "\n";
}