#### C++ Utilities
A collection of small utilities I like having around

* command_line
    * C++17
    * For processing command line arguments
    * Demonstrated in example_main.cpp
    

* config_reader
    * C++ 17
    * Read configuration file of key value pairs
    * key=value or key = value
    * Comment lines with '#'
    * Overload for specifying required keys


* directory_helper
    * C++17
    * Provides file paths of a given extension in a directory


* iterator
    * IndexRange
        * Iterate over a range of indeces from 0 to size - 1
    * PointRange2D
        * Iterate over a 2D array/matrix of given width and height


* leak_check
    * Check for memory leaks using Visual Studio


* libimage
    * Image processing library using Boost GIL
    * Add _CRT_SECURE_NO_WARNINGS to Preprocessor Definitions in Visual Studio


* normalize
    * C++17
    * For custom scaling of values from one range to another
    * convert_config.hpp
        * Set minimum and maximum values type of scaling e.g. linear or sigmoidal
        * Add any scaling schemes
    * normalize.hpp
        * Uses values set in convert_config.hpp to normalize a given value
    * charmap.hpp
        * Used with normalize.hpp to convert a given value to a character
        * Multiple values can be saved as strings
        * TODO: bytemap.hpp
    * convert.hpp/cpp
        * Used with charmap.hpp to convert multiple values into a string


* stopwatch
    * C++17
    * Wraps std::chrono to easily time code execution