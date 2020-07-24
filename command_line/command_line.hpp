#pragma once
#include <functional>
#include <vector>
#include <string>


namespace cmd
{
	//======= TYPES =================

	using args_t = std::vector<const char*>;
	using args_list_t = std::vector<args_t>;

	using validate_t = std::function<bool(args_t const&)>;
	using execute_t = std::function<void()>;

	typedef struct
	{
		const char* shrt;
		const char* lng;
		const char* description;
		validate_t validate;
		execute_t execute;

	} option_t;

	using option_list_t = std::vector<cmd::option_t>;


	//======= FUNCTIONS ==============

	void process_args(int argc, char* argv[], option_list_t const& options);

	std::string to_options_str(option_list_t const& options);

	bool has_extenstion(const char* path, std::string const& extension);


	// validate_t for option that takes no arguments
	inline bool no_args(args_t const& args) { return args.size() == 1; }

	// validate_t for option that takes one int argument
	bool one_int(args_t const& args);

	// validate_t for option that takes one double argument
	bool one_double(args_t const& args);

	// validate_t for option that takes one directory argument
	bool one_dir(args_t const& args);

	// validate_t for option that takes one file path argument
	bool one_file(args_t const& args);
}


