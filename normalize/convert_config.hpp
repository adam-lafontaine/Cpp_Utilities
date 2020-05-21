#pragma once

#include<array>

namespace convert_config
{
	// ======= RAW DATA PROPERTIES ======================

	// data close to this value is considered to be significantly less than DATA_VALUE_MID
	// e.g. minimum expected value from raw data
	// data with this value or less will be mapped to NORM_MIN
	constexpr double DATA_VALUE_MIN = 0;

	// data close to this value is considered to be significantly greater than DATA_VALUE_MID
	// e.g. maximum expected value from raw data
	// data with this value or more will be mapped to NORM_MAX
	constexpr double DATA_VALUE_MAX = 1000000;
	
	// data close to this value is considered not to have changed significantly
	// e.g. median, average, or expected value of the data
	// data with this value will be mapped to NORM_MID	
	constexpr double DATA_VALUE_MID = (DATA_VALUE_MAX - DATA_VALUE_MIN) / 2;

	//======= NORMALIZATION PROPERTIES ===================

	// raw data will be converted to a value >= NORM_MIN and <= NORM_MAX
	// will be scaled based on NORM_MID and the relationship defined by NORM_MAP
	constexpr double NORM_MIN = 0.0;
	constexpr double NORM_MAX = 1.0;
	constexpr double NORM_MID = 0.5;


	typedef struct norm_map_point_t
	{
		double x;
		double y;
	} norm_map_pt;


	// linear scaling for mapping raw data to normalized values
	// {0.0, 0.0} represents {DATA_VALUE_MID, NORM_MID}
	// {1.0, 1.0} represents {DATA_VALUE_MAX, NORM_MAX} and {DATA_VALUE_MIN, NORM_MIN}
	constexpr std::array<norm_map_pt, 2> make_norm_map_linear()
	{
		std::array<norm_map_pt, 2> pts = { {
			{0.0, 0.0},
			{1.0, 1.0}
		} };

		return pts;
	}


	// an example of sigmoidal scaling for mapping raw data to normalized values
	// {0.0, 0.0} represents {DATA_VALUE_MID, NORM_MID}
	// {1.0, 1.0} represents {DATA_VALUE_MAX, NORM_MAX} and {DATA_VALUE_MIN, NORM_MIN}
	// points in between dictate how values in between are scaled
	constexpr std::array<norm_map_pt, 6> make_norm_map_sigmoid()
	{
		std::array<norm_map_pt, 6> pts = { {
			{0.0, 0.0},
			{0.1, 0.4},
			{0.2, 0.6},
			{0.3, 0.7},
			{0.6, 0.9},
			{1.0, 1.0}
		} };

		return pts;
	}
	

	// choose scaling option here
	constexpr auto NORM_MAP = make_norm_map_linear();
}