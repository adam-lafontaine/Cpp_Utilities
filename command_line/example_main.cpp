#include "command_line.hpp"

#include <iostream>
#include <cstdlib>

constexpr auto HELP_DESC = " show usage options";
constexpr auto INT_DESC  = "  pass an int param => -i 42";
constexpr auto ADD_DESC  = "    add two numbers => -a 64 48";
constexpr auto FILE_DESC = "process a text file => -f ./src/my_file.txt";


//======= VALIDATION =======

bool is_two_doubles(cmd::args_t const& args);
bool is_text_file(cmd::args_t const& args);


//======= OPTIONS ================

bool help_option = false;
bool int_option = false;
bool add_option = false;
bool file_option = false;

int int_val = 0;
double d_val1 = 0;
double d_val2 = 0;
const char* text_file = "";

const cmd::option_list_t OPTIONS =
{													// values can be set in execute function
	{ "-h", "--help", HELP_DESC, cmd::no_args,   [](cmd::args_t const&)      { help_option = true; } },
    { "-i", "--int",  HELP_DESC, cmd::one_int,   [](cmd::args_t const& args) { int_option = true; int_val = std::atoi(args[1]); } },
    { "-a", "--add",  HELP_DESC, is_two_doubles, [](cmd::args_t const&)      { add_option = true; } },
	{ "-f", "--file", FILE_DESC, is_text_file,   [](cmd::args_t const& args) { file_option = true; text_file = args[1]; } },
};


//======= EXECUTION ==============

void show_help();
void process_int();
void process_doubles();
void process_file();
void show_error();


//======= MAIN ===================

int main(int argc, char* argv[])
{	
	cmd::process_args(argc, argv, OPTIONS);

    // options do not have to be mutually exclusive

	if (help_option)
	{
		show_help();
		return EXIT_SUCCESS;
	}
	else if (int_option)
	{
		process_int();
		return EXIT_SUCCESS;
	}
    else if (add_option)
	{
		process_doubles();
		return EXIT_SUCCESS;
	}
	else if (file_option)
	{
		process_file();
		return EXIT_SUCCESS;
	}

	show_error();
	return EXIT_FAILURE;
}


//======= IMPLEMENTATIONS ====================

bool is_two_doubles(cmd::args_t const& args)
{
    if (args.size() != 3)
		return false;

    const auto is_equal = [](const char* lhs, const char* rhs){ return std::strcmp(lhs, rhs) == 0; };

    const auto is_double = [&](const char* arg)
    {
        auto val = std::atof(arg);
        return val != 0 || (val == 0 && (is_equal(arg, "0") || is_equal(arg, "0.0"))); // 0.00?
    };

	// values can also be set in validation function
	if(is_double(args[1]) && is_double(args[2]))
	{
		d_val1 = std::atof(args[1]);
		d_val2 = std::atof(args[2]);
		return true;
	}

    return false;
}

bool is_text_file(cmd::args_t const& args)
{  	
    return cmd::one_file(args) && cmd::is_file_type(text_file, ".txt");
}

void show_help()
{
	std::cout << "Usage:\n" << cmd::to_options_str(OPTIONS);
}

void process_int()
{
    std::cout << "The number you entered is " << int_val << '\n';
}

void process_doubles()
{	
    std::cout << d_val1 << " + " << d_val2 << " = " << d_val1 + d_val2<< '\n';
}

void process_file()
{	
	std::cout << "You entered file: " << text_file << "\n";
}

void show_error()
{
	std::cout << "Error: You did it wrong.\n";
	show_help();
}