#pragma once

#include <string>
#include <vector>


namespace data_conversion
{
	using data_row_t = std::vector<double>;

	// convert value so that it can be mapped
	double convert_value(double value);

	// track min and max value found
	// can be used for adjusting DATA_VALUE_MIN and DATA_VALUE_MAX in convert_config.hpp
	double min_value();
	double max_value();

	// map a row of converted data to a string so that it can be written to file
	std::string data_to_string(data_row_t const& data_row);

	// map a line from file back to normalized data
	data_row_t string_to_data(std::string const& data_str);
}
