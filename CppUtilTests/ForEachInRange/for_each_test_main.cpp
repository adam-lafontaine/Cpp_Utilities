#include "../../for_each_in_range/for_each_in_range.hpp"

#include <iostream>

namespace fseq = for_each_in_range::seq;

int main()
{
	size_t width = 10;
	size_t height = 20;

	auto const id_func = [&](auto id) { std::cout << id << '\n'; };

	fseq::for_each_in_range(width, id_func);
}