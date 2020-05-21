#pragma once

#include "convert_config.hpp"

namespace cfg = convert_config;

namespace normalize_data
{	
	// redefine constants
	constexpr auto N_MIN = cfg::NORM_MIN;
	constexpr auto N_MAX = cfg::NORM_MAX;
	constexpr auto N_MID = cfg::NORM_MID;
	constexpr auto D_MIN = cfg::DATA_VALUE_MIN;
	constexpr auto D_MAX = cfg::DATA_VALUE_MAX;
	constexpr auto D_MID = cfg::DATA_VALUE_MID;

	// size of NORM_MAP used in calculations
	constexpr auto  NORM_PTS_SZ = cfg::NORM_MAP.size();


	// algorithm for converting a value of raw data to a normalized value
	// between N_MIN and N_MAX
	constexpr double normalize(double val)
	{
		if (val <= D_MIN)
			return N_MIN;

		if (val >= D_MAX)
			return N_MAX;

		if (val == D_MID)
			return N_MID;

		double delta = 0;
		double n_val = 0;
		if (val > D_MID)
		{
			delta = N_MAX - N_MID;
			n_val = (val - D_MID) / (D_MAX - D_MID);
		}
		else
		{
			delta = N_MIN - N_MID;
			n_val = (D_MID - val) / (D_MID - D_MIN);
		}

		// locate x range of n_val within NORM_MAP
		size_t i = 1;
		for (; i < NORM_PTS_SZ && cfg::NORM_MAP[i].x < n_val; ++i)
			;

		// get upper and lower points
		auto lower = cfg::NORM_MAP[i - 1];
		auto upper = cfg::NORM_MAP[i];

		// find interpolation ratio between located values in NORM_MAP
		auto lerp_ratio = lower.y + (upper.y - lower.y) * (n_val - lower.x) / (upper.x - lower.x);

		return cfg::NORM_MID + delta * lerp_ratio;
	}
}