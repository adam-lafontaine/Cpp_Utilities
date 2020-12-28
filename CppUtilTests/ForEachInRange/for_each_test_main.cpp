#include "../../for_each_in_range/for_each_in_range.hpp"

#include <iostream>
#include <mutex>
#include <vector>

namespace fseq = for_each_in_range::seq;
namespace fpar = for_each_in_range::par;

std::mutex console_mtx;


void print_ranges();
void modify_ranges();

int main()
{
	print_ranges();

	modify_ranges();
	
}


void print_ranges()
{
	size_t width = 10;
	size_t height = 20;
	size_t x_begin = 2;
	size_t x_end = 9;
	size_t y_begin = 1;
	size_t y_end = 15;
	long long s_x_begin = -4;
	long long s_x_end = 2;
	long long s_y_begin = -3;
	long long s_y_end = 5;


	auto const id_out = [](auto id) { std::lock_guard<std::mutex> lk(console_mtx); std::cout << id << ", "; };

	std::cout << "1D Sequential:\n";

	fseq::for_each_in_range(width, id_out);
	std::cout << '\n';
	fseq::for_each_in_range(x_begin, x_end, id_out);
	std::cout << '\n';
	fseq::for_each_in_range(s_x_begin, s_x_end, id_out);
	std::cout << '\n';

	std::cout << "\n1D Parallel:\n";

	fpar::for_each_in_range(width, id_out);
	std::cout << '\n';
	fpar::for_each_in_range(x_begin, x_end, id_out);
	std::cout << '\n';
	fpar::for_each_in_range(s_x_begin, s_x_end, id_out);
	std::cout << '\n';


	auto max_per_line = width;
	unsigned on_line = 0;

	auto const xy_out = [&](auto x, auto y)
	{
		std::lock_guard<std::mutex> lk(console_mtx);
		if (on_line == max_per_line)
		{
			on_line = 0;
			std::cout << '\n';
		}

		printf("{ %2i, %2i }", x, y);

		//std::cout << "{ " << x << ", " << y << " } ";
		++on_line;
	};

	auto const pt_out = [&](auto const& pt) { xy_out(pt.x, pt.y); };

	std::cout << "\n\n2D width, height, pt - Sequential:\n";
	fseq::for_each_in_range_2d(width, height, pt_out);

	std::cout << "\n\n2D width, height, pt - Parallel:\n";
	on_line = 0;
	fpar::for_each_in_range_2d(width, height, pt_out);

	std::cout << "\n\n2D width, height, xy - Sequential:\n";
	on_line = 0;
	fseq::for_each_in_range_2d(width, height, xy_out);

	std::cout << "\n\n2D width, height, xy - Parallel:\n";
	on_line = 0;
	fpar::for_each_in_range_2d(width, height, xy_out);

	max_per_line = x_end - x_begin;
	std::cout << "\n\n2D begin, end, xy - Sequential:\n";
	on_line = 0;
	fseq::for_each_in_range_2d(x_begin, x_end, y_begin, y_end, xy_out);

	std::cout << "\n\n2D begin, end, xy - Parallel:\n";
	on_line = 0;
	fpar::for_each_in_range_2d(x_begin, x_end, y_begin, y_end, xy_out);

	max_per_line = s_x_end - s_x_begin;
	std::cout << "\n\n2D begin, end, xy signed - Sequential:\n";
	on_line = 0;
	fseq::for_each_in_range_2d(s_x_begin, s_x_end, s_y_begin, s_y_end, xy_out);

	std::cout << "\n\n2D begin, end, xy signed - Parallel:\n";
	on_line = 0;
	fpar::for_each_in_range_2d(s_x_begin, s_x_end, s_y_begin, s_y_end, xy_out);

	std::cout << "\n\n";
}


void print_1d(std::vector<int> const& list)
{
	for(auto i : list)
		std::cout << i << ", ";

	std::cout << '\n';
}


void print_2d(std::vector<std::vector<int>> const& list_2d)
{
	for (auto const& list : list_2d)
	{
		print_1d(list);
	}

	std::cout << '\n';
}


std::vector<std::vector<int>> make_2d(size_t w, size_t h)
{
	std::vector<std::vector<int>> list_2d;
	list_2d.reserve(h);

	for (size_t i = 0; i < h; ++i)
		list_2d.push_back(std::vector<int>(w, 0));

	return list_2d;
}


void modify_ranges()
{
	size_t width = 10;
	size_t height = 20;
	size_t x_begin = 2;
	size_t x_end = 9;
	size_t y_begin = 1;
	size_t y_end = 15;
	
	
	auto num_list = std::vector<int>(width, 0);

	auto const set_num = [&](auto id) { num_list[id] = 1; };

	std::cout << "1D Sequential:\n";
	print_1d(num_list);	
	fseq::for_each_in_range(width, set_num);
	print_1d(num_list);

	std::cout << "\n1D Parallel:\n";
	num_list = std::vector<int>(width, 0);
	print_1d(num_list);
	fseq::for_each_in_range(width, set_num);
	print_1d(num_list);


	auto list_2d = make_2d(width, height);
	auto const set_pt = [&](auto const& pt) { list_2d[pt.y][pt.x] = 1; };
	auto const set_xy = [&](auto x, auto y) { list_2d[y][x] = 1; };


	std::cout << "\n\n2D width, height, pt - Sequential:\n";
	print_2d(list_2d);
	fseq::for_each_in_range_2d(width, height, set_pt);
	print_2d(list_2d);

	std::cout << "\n\n2D width, height, pt - Parallel:\n";
	list_2d = make_2d(width, height);
	print_2d(list_2d);
	fpar::for_each_in_range_2d(width, height, set_pt);
	print_2d(list_2d);

	std::cout << "\n\n2D width, height, xy - Sequential:\n";
	list_2d = make_2d(width, height);
	print_2d(list_2d);
	fseq::for_each_in_range_2d(width, height, set_xy);
	print_2d(list_2d);

	std::cout << "\n\n2D width, height, xy - Parallel:\n";
	list_2d = make_2d(width, height);
	print_2d(list_2d);
	fpar::for_each_in_range_2d(width, height, set_xy);
	print_2d(list_2d);

	
	std::cout << "\n\n2D begin, end, xy - Sequential:\n";
	list_2d = make_2d(width, height);
	print_2d(list_2d);
	fseq::for_each_in_range_2d(x_begin, x_end, y_begin, y_end, set_xy);
	print_2d(list_2d);

	std::cout << "\n\n2D begin, end, xy - Parallel:\n";
	list_2d = make_2d(width, height);
	print_2d(list_2d);
	fpar::for_each_in_range_2d(x_begin, x_end, y_begin, y_end, set_xy);
	print_2d(list_2d);

}
