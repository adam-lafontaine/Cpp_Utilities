#include "convert.hpp"
#include "charmap.hpp"

namespace data_conversion
{
	// track min and max value found
	// can be used for adjusting DATA_VALUE_MIN and DATA_VALUE_MAX in convert_config.hpp
	double data_min = DBL_MAX;
	double data_max = -DBL_MAX;
	double min_value() { return data_min; }
	double max_value() { return data_max; }

	// convert value so that it can be mapped
	double convert_value(double value)
	{
		// track min and max values found
		if (value > data_max)
			data_max = value;

		if (value < data_min)
			data_min = value;

		// normalize to value between set minimum and maximum
		auto norm = charmap::nrm::normalize(value);

		// map to available value
		return charmap::to_value(norm);
	}


	// map a row of converted data to a string so that it can be written to file
	std::string data_to_string(data_row_t const& data_row)
	{
		std::string str;
		str.reserve(data_row.size());

		for (auto const val : data_row)
		{
			char ch = charmap::to_char(val);
			str += ch;
		}

		return str;
	}


	// map a line from file back to normalized data
	data_row_t string_to_data(std::string const& data_str)
	{
		data_row_t data;
		data.reserve(data_str.length());

		for (auto const ch : data_str)
		{
			data.push_back(charmap::to_value(ch));
		}

		return data;
	}
}

