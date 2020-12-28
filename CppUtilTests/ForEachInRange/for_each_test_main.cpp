#include "../../for_each_in_range/for_each_in_range.hpp"

#include <iostream>
#include <mutex>

namespace fseq = for_each_in_range::seq;
namespace fpar = for_each_in_range::par;

std::mutex console_mtx;



int main()
{
	size_t width = 10;
	size_t height = 20;
	size_t x_begin = 2;
	size_t x_end = 9;
	size_t y_begin = 1;
	size_t y_end = 15;
	long long s_x_begin = -9;
	long long s_x_end = 10;

	auto const id_out = [](auto id) { std::lock_guard<std::mutex> lk(console_mtx); std::cout << id << ", "; };

	std::cout << "Sequential:\n";

	fseq::for_each_in_range(width, id_out);
	std::cout << '\n';
	fseq::for_each_in_range(x_begin, x_end, id_out);
	std::cout << '\n';
	fseq::for_each_in_range(s_x_begin, s_x_end, id_out);
	std::cout << '\n';

	std::cout << "\nParallel:\n";

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

		std::cout << "{ " << x << ", " << y << " } ";
		++on_line;
	};

	auto const pt_out = [&](auto const& pt) { xy_out(pt.x, pt.y); };

	std::cout << "\n\nSequential:\n";
	fseq::for_each_in_range_2d(width, height, pt_out);

	std::cout << "\n\nParallel:\n";
	on_line = 0;
	fpar::for_each_in_range_2d(width, height, pt_out);

	/*max_per_line = x_end - x_begin;
	std::cout << "\n\nSequential:\n";
	on_line = 0;
	fseq::for_each_in_range_2d(x_begin, x_end, y_begin, y_end, xy_out);		

	std::cout << "\n\nParallel:\n";
	on_line = 0;
	fpar::for_each_in_range_2d(x_begin, x_end, y_begin, y_end, xy_out);*/
}