#include "command_line.hpp"

#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

namespace cmd
{

	//======= HELPERS ============================

	args_list_t get_args(int argc, char* argv[])
	{
		args_list_t list;
		for (int i = 1; i < argc; ++i)
		{
			if (argv[i][0] == '-')
				list.push_back(args_t());

			list.back().push_back(argv[i]);
		}

		return list;
	}


	bool is_equal(const char* lhs, const char* rhs)
	{
		return std::strcmp(lhs, rhs) == 0;
	}


	bool has_option(const char* arg, option_t const& opt)
	{
		return is_equal(arg, opt.shrt) || is_equal(arg, opt.lng);
	}


	std::string to_option_str(option_t const& opt)
	{
		return std::string(
			std::string(opt.shrt)
			+ std::string(", ")
			+ std::string(opt.lng)
			+ std::string(": ")
			+ std::string(opt.description)
		);
	}


	//======= PUBLIC =================

	void process_args(int argc, char* argv[], option_list_t const& options)
	{
		auto arg_list = get_args(argc, argv);

		for (auto const& args : arg_list)
		{
			for (auto const& opt : options)
			{
				if (has_option(args[0], opt) && opt.validate(args))
				{
					opt.execute(args);
				}
			}
		}
	}


	std::string to_options_str(option_list_t const& options)
	{
		std::string out;

		for (auto const& opt : options)
		{
			out += to_option_str(opt) + '\n';
		}

		return out;
	}


	bool has_extenstion(const char* file_path, std::string const& extension)
	{
		if (extension[0] != '.')
			return false;

		auto path = fs::path(file_path);
		return path.has_extension() && path.extension() == extension;
	}


	bool one_int(args_t const& args)
	{
		if (args.size() != 2)
			return false;

		auto val = std::atoi(args[1]);
		return val != 0 || (val == 0 && is_equal(args[1], "0"));
	}


	bool one_double(args_t const& args)
	{
		if (args.size() != 2)
			return false;

		auto val = std::atof(args[1]);
		return val != 0 || (val == 0 && (is_equal(args[1], "0") || is_equal(args[1], "0.0"))); // 0.00?
	}


	bool one_dir(args_t const& args)
	{
		return args.size() == 2 && fs::exists(args[1]) && fs::is_directory(args[1]);
	}


	bool one_file(args_t const& args)
	{
		return args.size() == 2 && fs::exists(args[1]) && fs::is_regular_file(args[1]);
	}
}

