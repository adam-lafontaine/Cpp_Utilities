#include "../../libimage/libimage.hpp"

#include <iostream>
#include <mutex>

namespace fs = std::filesystem;
namespace img = libimage;

constexpr auto SRC_IMAGE_PATH = "D:/repos/Cpp_Utilities/CppUtilTests/LibImage/in_files/png/corvette.png";
constexpr auto DST_IMAGE_ROOT = "D:/repos/Cpp_Utilities/CppUtilTests/LibImage/out_files";


void empty_dir(fs::path const& dir);
void print(img::view_t const& view);
void print(img::gray::view_t const& view);
void print(img::stats_t const& stats);

void basic_tests(fs::path const& out_dir);
void for_each_tests(fs::path const& out_dir);
void transform_tests(fs::path const& out_dir);
void math_tests();


int main()
{
	auto dst_root = fs::path(DST_IMAGE_ROOT);
	empty_dir(dst_root);

	//basic_tests(dst_root);
	//(dst_root);
	//transform_tests(dst_root);
	math_tests();
}


void math_tests()
{
	std::cout << "math:\n";

	auto image = img::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view = img::make_view(image);

	auto stats = img::make_stats(view);
	std::cout << "  red: ";
	print(stats.r);
	std::cout << "green: ";
	print(stats.g);
	std::cout << " blue: ";
	print(stats.b);

	auto image_gray = img::gray::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view_gray = img::make_view(image_gray);

	auto stats_gray = img::make_stats(view_gray);
	std::cout << " gray: ";
	print(stats_gray);

	img::pixel_range_t range;
	range.x_begin = 245;
	range.x_end = 345;
	range.y_begin = 270;
	range.y_end = 300;

	stats = img::make_stats(view, range);
	std::cout << "  range red: ";
	print(stats.r);
	std::cout << "range green: ";
	print(stats.g);
	std::cout << " range blue: ";
	print(stats.b);

	stats_gray = img::make_stats(view_gray, range);
	std::cout << " range gray: ";
	print(stats_gray);

	std::cout << '\n';
}


void transform_tests(fs::path const& out_dir)
{
	std::cout << "transform_pixels:\n";

	auto image = img::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view = img::make_view(image);

	auto const func = [](img::pixel_t const& p) { return img::to_pixel(p[0] / 2, p[1] / 2, p[2] / 2); };
	auto dst_image = img::image_t(image.width(), image.height());
	auto dst_view = img::make_view(dst_image);
	img::seq::transform_pixels(view, dst_view, func);
	img::write_image_view(out_dir / "transform_seq.png", dst_view);
	img::par::transform_pixels(view, dst_view, func);
	img::write_image_view(out_dir / "transform_par.png", dst_view);

	auto image_gray = img::gray::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view_gray = img::make_view(image_gray);

	auto const func_gray = [](img::gray::pixel_t const& p) { return img::gray::pixel_t(p[0] / 2); };
	auto dst_image_gray = img::gray::image_t(image_gray.width(), image_gray.height());
	auto dst_view_gray = img::make_view(dst_image_gray);
	img::seq::transform_pixels(view_gray, dst_view_gray, func_gray);
	img::write_image_view(out_dir / "transform_gray_seq.png", dst_view_gray);
	img::par::transform_pixels(view_gray, dst_view_gray, func_gray);
	img::write_image_view(out_dir / "transform_gray_par.png", dst_view_gray);

	std::cout << '\n';
}


void for_each_tests(fs::path const& out_dir)
{
	std::cout << "for_each_pixel:\n";
	using uint_t = unsigned long long;
	std::mutex mtx;

	auto image = img::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view = img::make_view(image);

	uint_t total_red = 0;
	auto const count_func = [&](img::pixel_t const& p) { total_red += img::to_rgba(p).r; };
	img::seq::for_each_pixel(view, count_func);
	std::cout << "red seq: " << total_red << "\n";

	total_red = 0;
	auto const lk_count_func = [&](img::pixel_t const& p) { std::lock_guard<std::mutex> lk(mtx); total_red += img::to_rgba(p).r; };
	img::par::for_each_pixel(view, lk_count_func);
	std::cout << "red par: " << total_red << "\n";

	auto image_gray = img::gray::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view_gray = img::make_view(image_gray);

	uint_t total_gray = 0;
	auto const count_func_gray = [&](img::gray::pixel_t const& p) { total_gray += p; };
	img::seq::for_each_pixel(view_gray, count_func_gray);
	std::cout << "gray seq: " << total_gray << "\n";

	total_gray = 0;
	auto const lk_count_func_gray = [&](img::gray::pixel_t const& p) { std::lock_guard<std::mutex> lk(mtx); total_gray += p; };
	img::par::for_each_pixel(view_gray, lk_count_func_gray);
	std::cout << "gray par: " << total_gray << "\n";


	auto const red_func = [](img::pixel_t& p) { p[0] /= 2; };
	img::seq::for_each_pixel(view, red_func);
	img::write_image_view(out_dir / "for_each_seq.png", view);
	img::par::for_each_pixel(view, red_func);
	img::write_image_view(out_dir / "for_each_par.png", view);


	auto const gray_func = [](img::gray::pixel_t& p) { p[0] /= 2; };
	img::seq::for_each_pixel(view_gray, gray_func);
	img::write_image_view(out_dir / "for_each_gray_seq.png", view_gray);
	img::par::for_each_pixel(view_gray, gray_func);
	img::write_image_view(out_dir / "for_each_gray_par.png", view_gray);

	std::cout << '\n';
}


void basic_tests(fs::path const& out_dir)
{
	std::cout << "basic:\n";

	auto image = img::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view = img::make_view(image);
	print(view);

	auto w = view.width();
	auto h = view.height();

	auto resized_image = img::image_t(h, w);
	auto resized_view = img::make_resized_view(image, resized_image);
	print(resized_view);
	img::write_image_view(out_dir / "resized.png", resized_view);

	img::pixel_range_t range = { w * 1 / 3, w * 2 / 3, h * 1 / 3, h * 2 / 3 };
	auto sub_view = img::sub_view(view, range);
	print(sub_view);
	img::write_image_view(out_dir / "sub.png", sub_view);

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
	img::write_image_view(out_dir / "resized_gray.png", resized_view_gray);

	auto sub_view_gray = img::sub_view(view_gray, range);
	print(sub_view_gray);
	img::write_image_view(out_dir / "sub_gray.png", sub_view_gray);

	auto row_view_gray = img::row_view(view, 2);
	print(row_view_gray);

	auto col_view_gray = img::column_view(view, 2);
	print(col_view_gray);

	std::cout << '\n';
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


void print(img::stats_t const& stats)
{
	std::cout << "mean = " << (double)stats.mean << " sigma = " << (double)stats.sigma << '\n';
}