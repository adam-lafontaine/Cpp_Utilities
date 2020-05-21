#pragma once
#include "normalize.hpp"

#include<algorithm>
#include <cstdlib>
#include <limits>

// Used for mapping normalized data to char and vice versa
// for reading and writing data to/form files

namespace charmap
{
	namespace nrm = normalize_data;

	//====== TYPES =====================

	typedef struct CharMapPair
	{
		double val;
		char ch;
	} pair;

	//======= CONSTANT LITERALS =================

	constexpr double MIN_VAL = nrm::N_MIN;
	constexpr double MAX_VAL = nrm::N_MAX;

	// printable characters
	constexpr char MIN_CHAR = 33;
	constexpr char MAX_CHAR = 126;

	constexpr double NO_VAL = std::numeric_limits<double>::quiet_NaN();
	constexpr char NO_CHAR = ' ';

	constexpr size_t NUM_ELE = MAX_CHAR - MIN_CHAR + 1;

	//======= HELPERS===========================

	constexpr double round_to_3(double num)
	{
		return (double)((int)(num * 1000)) / 1000.0;
	}

	// calculate the value an index will map to 
	constexpr double calc_val_from_index(size_t i)
	{
		return round_to_3(MIN_VAL + (double)i / (NUM_ELE - 1) * (MAX_VAL - MIN_VAL));
	}

	// get the char that an array index will map to
	constexpr char find_char_from_index(size_t idx)
	{
		return MIN_CHAR + (char)idx;
	}

	//======= GENERATE PAIRS ===================

	constexpr std::array<pair, NUM_ELE> make_pairs()
	{
		std::array<pair, NUM_ELE> data{ 0 };
		for (size_t i = 0; i < NUM_ELE; ++i)
		{
			// C++17 constexpr
			data[i] =
			{
				calc_val_from_index(i),
				find_char_from_index(i)
			};
		}

		return data;
	}

	constexpr auto pairs = make_pairs();

	//======= PUBLIC ======================

	constexpr double to_value(size_t idx)
	{
		return pairs[idx].val;
	}

	constexpr char to_char(size_t idx)
	{
		return pairs[idx].ch;
	}

	constexpr size_t to_index(char ch)
	{
		char char_idx = ch - MIN_CHAR;
		return (size_t)char_idx;
	}

	// map a char back to a value after reading file
	constexpr double to_value(char ch)
	{
		if (ch == NO_CHAR)
			return NO_VAL;

		return to_value(to_index(ch));
	}

	// find the index that best maps to value
	constexpr size_t to_index(double val)
	{
		const double tolerance = 0.0001;
		const size_t i_start = val < 0 ? 0 : NUM_ELE / 2;

		size_t i = i_start;		
		for (; val - pairs[i].val > tolerance; ++i)
			;

		return i;
	}

	// map a value to a char for writing
	constexpr char to_char(double val)
	{
		if (val != val) // nan
			return NO_CHAR;

		return to_char(to_index(val));
	}


	constexpr double to_value(double val)
	{
		if (val != val)
			return val;

		return pairs[to_index(val)].val;
	}
	
}